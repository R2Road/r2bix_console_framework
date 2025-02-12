#include "r2bix_director_ScreenBufferManager.h"

#include <cassert>
#include <iostream>
#include <Windows.h>

//
// for Windows.h
// - wtf... o_o;;;
//
#undef min
#undef max

#include "r2bix_render_Texture.h"

namespace r2bix_director
{
	ScreenBufferManager::ScreenBufferManager() :
		  mBufferHandleOriginal( INVALID_HANDLE_VALUE )
		, mCoutOriginalStreamBuffer( nullptr )

		, mBufferHandleList()
		, mCoutBufferRedirectorList()

		, mCurrentBufferIndex( 0 )
	{
		init();
	}
	ScreenBufferManager::~ScreenBufferManager()
	{
		release();
	}

	void ScreenBufferManager::init()
	{
		//
		// # 20220215 - R
		// Debug, Release 모두 CreateConsoleScreenBuffer에 실패해도 터지지 않는다.
		// SetConsoleActiveScreenBuffer에 INVALID_HANDLE_VALUE 가 들어가면 아무 작동도 하지 않는다.
		//

		//
		// Backup
		//
		mBufferHandleOriginal = GetStdHandle( STD_OUTPUT_HANDLE );
		mCoutOriginalStreamBuffer = std::cout.rdbuf();


		CONSOLE_SCREEN_BUFFER_INFO csbi{};
		if( !GetConsoleScreenBufferInfo( mBufferHandleOriginal, &csbi ) )
		{
			assert( false && "Failed : GetConsoleScreenBufferInfo" );
		}


		for( int i = 0; BUFFER_COUNT > i; ++i )
		{
			mBufferHandleList[i] = CreateConsoleScreenBuffer(
				GENERIC_READ | GENERIC_WRITE
				, 0//FILE_SHARE_WRITE | FILE_SHARE_READ
				, nullptr
				, CONSOLE_TEXTMODE_BUFFER
				, nullptr
			);
			assert( INVALID_HANDLE_VALUE != mBufferHandleList[i] );
			mCoutBufferRedirectorList[i] = CoutBufferRedirector( mBufferHandleList[i] );

			if( !SetConsoleScreenBufferSize( mBufferHandleList[i], csbi.dwSize ) )
			{
				assert( false && "Failed : SetConsoleScreenBufferSize" );
			}
		}

		//
		// Cursor
		//
		{
			SetCursorVisibility( false );
		}
	}

	void ScreenBufferManager::release()
	{
		SetCursorVisibility( true );

		//
		// Rollback
		//
		if( INVALID_HANDLE_VALUE != mBufferHandleOriginal )
		{
			SetConsoleActiveScreenBuffer( mBufferHandleOriginal );
			std::cout.rdbuf( mCoutOriginalStreamBuffer );
		}

		//
		// Close Handle List
		//
		for( int i = 0; BUFFER_COUNT > i; ++i )
		{
			CloseHandle( mBufferHandleList[i] );
		}
	}
	void ScreenBufferManager::SetCursorVisibility( const bool visible )
	{
		for( int i = 0; BUFFER_COUNT > i; ++i )
		{
			if( INVALID_HANDLE_VALUE != mBufferHandleList[i] )
			{
				setCursorVisibilityProcess( mBufferHandleList[i], visible );
			}
		}
	}
	void ScreenBufferManager::setCursorVisibilityProcess( HandleT handle, const bool visible )
	{
		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo( handle, &cursorInfo );
		cursorInfo.bVisible = visible;
		SetConsoleCursorInfo( handle, &cursorInfo );
	}

	void ScreenBufferManager::SetCursorPosition( const short x, const short y )
	{
		setCursorPositionProcess( mBufferHandleList[mCurrentBufferIndex], x, y );
	}
	void ScreenBufferManager::setCursorPositionProcess( HandleT handle, const short x, const short y )
	{
		SetConsoleCursorPosition( handle, COORD{ x, y } );
	}



	void ScreenBufferManager::ClearBufferColor( const short x, const short y, const int length )
	{
		clearBufferColorProcess( mBufferHandleList[mCurrentBufferIndex], x, y, length, 7 );
	}
	void ScreenBufferManager::clearBufferColorProcess( HandleT handle, const short x, const short y, const int length, const unsigned short color )
	{
		DWORD out_result;
		FillConsoleOutputAttribute( handle, color, length, { x, y }, &out_result );
	}



	void ScreenBufferManager::ClearCurrentBuffer()
	{
		clearBufferProcess( mBufferHandleList[mCurrentBufferIndex] );
	}
	void ScreenBufferManager::clearBufferProcess( HandleT handle )
	{
		CONSOLE_SCREEN_BUFFER_INFO cs_buffer_info{};
		DWORD out_result;
		GetConsoleScreenBufferInfo( handle, &cs_buffer_info );
		const DWORD length = cs_buffer_info.dwSize.X * cs_buffer_info.dwSize.Y;

		FillConsoleOutputCharacter( handle, TEXT( ' ' ), length, { 0, 0 }, &out_result );

		SetConsoleCursorPosition( handle, { 0, 0 } );
	}



	void ScreenBufferManager::Write2BackBuffer( const short offset_x, const short offset_y, const r2bix_render::Texture* const texture )
	{
		int next_buffer_index = mCurrentBufferIndex + 1;
		if( BUFFER_COUNT <= next_buffer_index )
		{
			next_buffer_index = 0;
		}

		write2BufferProcess( mBufferHandleList[next_buffer_index], offset_x, offset_y, texture );
	}
	void ScreenBufferManager::write2BufferProcess( HandleT handle, const short offset_x, const short offset_y, const r2bix_render::Texture* const texture )
	{
		const COORD write_offset_coord = { offset_x, offset_y };
		COORD current_write_coord;
		DWORD out_result;

		std::string_view output_line;
		const r2bix::ColorValue* color_line;
		for( SHORT y = 0, end_y = static_cast< SHORT >( texture->GetHeight() ); end_y > y; ++y )
		{
			current_write_coord = write_offset_coord;
			current_write_coord.Y += y;

			//
			// Character
			//
			output_line = texture->GetCharacterLine( static_cast< uint32_t >( y ) );
			WriteConsoleOutputCharacterA( handle, output_line.data(), static_cast< DWORD >( output_line.length() ), current_write_coord, &out_result );

			//
			// Color
			//
			color_line = texture->GetColorLine( static_cast< uint32_t >( y ) );
			WriteConsoleOutputAttribute( handle, ( WORD* )( color_line ), static_cast< DWORD >( output_line.length() ), current_write_coord, &out_result );
		}
	}



	void ScreenBufferManager::Swap()
	{
		//
		// Update Index
		//
		++mCurrentBufferIndex;
		if( BUFFER_COUNT <= mCurrentBufferIndex )
		{
			mCurrentBufferIndex = 0;
		}

		//
		// Swap
		//
		SetConsoleActiveScreenBuffer( mBufferHandleList[mCurrentBufferIndex] );
		std::cout.rdbuf( &mCoutBufferRedirectorList[mCurrentBufferIndex] );
	}



	std::string ScreenBufferManager::OpenTextInputBuffer(
		  const short offset_x, const short offset_y
		, const short input_x, const short input_y, const int length
		, const r2bix_render::Texture* const texture
	)
	{
		std::string s;

		if( INVALID_HANDLE_VALUE != mBufferHandleOriginal )
		{
			//
			// Buffer Setup
			//
			SetConsoleActiveScreenBuffer( mBufferHandleOriginal );
			std::cout.rdbuf( mCoutOriginalStreamBuffer );

			//
			// Clear
			//
			clearBufferProcess( mBufferHandleOriginal );

			//
			// Fill
			//
			write2BufferProcess( mBufferHandleOriginal, offset_x, offset_y, texture );

			//
			// Cursor Visibility
			//
			setCursorVisibilityProcess( mBufferHandleOriginal, true );

			//
			// Cursor Position
			//
			setCursorPositionProcess( mBufferHandleOriginal, input_x, input_y );

			//
			// Clear Buffer Color
			//
			clearBufferColorProcess( mBufferHandleOriginal, input_x, input_y, length, 10 | 0 ); // FG_LightGreen | BG_Black

			//
			// Input
			//
			std::cin >> s;
			if( length < s.length() )
			{
				s.resize( length );
			}

			//
			// Rollback
			//
			Swap();
		}

		return s;
	}
}