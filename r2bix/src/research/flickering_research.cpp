#include "pch.h"
#include "flickering_research.h"

#include <conio.h> // _kbhit(), _getch()
#include <Windows.h> // HANDLE, COORD, SetConsoleCursorPosition()

#include "base/r2base_eTestEndAction.h"

#include "render/r2render_Texture.h"
#include "render/r2render_FrameBuffer.h"

namespace flickering_research
{
	r2base::iTest::TitleFunc OneByOne::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering : Print One By One";
		};
	}
	r2base::iTest::DoFunc OneByOne::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			r2render::Texture visible_resource( 19, 19 );
			visible_resource.FillAll( 'a' );

			bool process = true;
			do
			{
				system( "cls" );

				std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
				std::cout << "[Any Key] End" << r2::linefeed;

				std::cout << r2::split;

				int current_x = 0;
				for( const auto v : visible_resource )
				{
					if( visible_resource.GetWidth() <= current_x )
					{
						std::cout << r2::linefeed;
						current_x = 0;
					}

					std::cout << v;

					++current_x;
				}

				std::cout << r2::linefeed << r2::split;

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2base::eTestEndAction::None;
		};
	}
	r2base::iTest::TitleFunc OneByOne_WithOut_CLS::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering : Print One By One WithOut CLS";
		};
	}
	r2base::iTest::DoFunc OneByOne_WithOut_CLS::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
			std::cout << "[Any Key] End" << r2::linefeed;

			std::cout << r2::split;
			std::cout << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed3 << r2::linefeed;
			std::cout << r2::split;

			r2render::Texture visible_resource( 19, 19 );
			visible_resource.FillAll( 'a' );

			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			const COORD pos = { 0, 6 };

			bool process = true;
			do
			{
				SetConsoleCursorPosition( stdHandle, pos );

				int current_x = 0;
				for( const auto v : visible_resource )
				{
					if( visible_resource.GetWidth() <= current_x )
					{
						std::cout << r2::linefeed;
						current_x = 0;
					}

					std::cout << v;

					++current_x;
				}

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2base::eTestEndAction::None;
		};
	}



	r2base::iTest::TitleFunc LineByLine::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering : Print Line By Line";
		};
	}
	r2base::iTest::DoFunc LineByLine::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			r2render::Texture visible_resource( 19, 19 );
			visible_resource.FillAll( 'a' );

			bool process = true;
			do
			{
				system( "cls" );

				std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
				std::cout << "[Any Key] End" << r2::linefeed;

				std::cout << r2::split;

				for( int current_y = 0; visible_resource.GetHeight() > current_y; ++current_y )
				{
					std::cout << visible_resource.GetLine( current_y ) << r2::linefeed;
				}

				std::cout << r2::split;

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2base::eTestEndAction::None;
		};
	}



	r2base::iTest::TitleFunc PageByPage::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering : Print Page By Page";
		};
	}
	r2base::iTest::DoFunc PageByPage::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			r2render::FrameBuffer frame_buffer( 5, 5 );
			frame_buffer.FillAll( 'c' );

			bool process = true;
			do
			{
				system( "cls" );

				std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed2;
				std::cout << "[Any Key] End" << r2::linefeed;

				std::cout << r2::split;

				std::cout << &( *frame_buffer.begin() );

				std::cout << r2::split;

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2base::eTestEndAction::None;
		};
	}



	r2base::iTest::TitleFunc PageByPage_WithOut_CLS_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering : Print Page By Page Without CLS 1";
		};
	}
	r2base::iTest::DoFunc PageByPage_WithOut_CLS_1::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			r2render::FrameBuffer frame_buffer( 100, 40 );
			frame_buffer.FillAll( 'c' );

			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			const COORD pos = { 0, 0 };

			bool process = true;
			do
			{
				SetConsoleCursorPosition( stdHandle, pos );

				std::cout << &( *frame_buffer.begin() );

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2base::eTestEndAction::None;
		};
	}



	r2base::iTest::TitleFunc PageByPage_WithOut_CLS_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Flickering : Print Page By Page Without CLS 2";
		};
	}
	r2base::iTest::DoFunc PageByPage_WithOut_CLS_2::GetDoFunction()
	{
		return []( r2base::Director& )->r2base::eTestEndAction
		{
			r2render::FrameBuffer frame_buffer_1( 100, 40 );
			frame_buffer_1.FillAll( 'c' );

			r2render::FrameBuffer frame_buffer_2( 100, 40 );
			frame_buffer_2.FillAll( 'a' );

			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			const COORD pos = { 0, 0 };
			bool bDrawTarget = true;

			bool process = true;
			do
			{
				SetConsoleCursorPosition( stdHandle, pos );

				if( bDrawTarget )
				{
					std::cout << &( *frame_buffer_1.begin() );
				}
				else
				{
					std::cout << &( *frame_buffer_2.begin() );
				}

				bDrawTarget = !bDrawTarget;

				//
				// Input
				//
				if( _kbhit() )
				{
					_getch(); // need
					process = false;
				}

			} while( process );

			return r2base::eTestEndAction::None;
		};
	}
}