#pragma once

#include <string>

#include "r2/r2_Point.h"

#include "r2bix_director_CoutBufferRedirector.h"

namespace r2bix_render
{
	class Texture;
}

namespace r2bix_director
{
	class ScreenBufferManager
	{
	private:
		using HandleT = void*;
		enum { BUFFER_COUNT = 2 };



	public:
		ScreenBufferManager();
		ScreenBufferManager( const short x, const short y );
		~ScreenBufferManager();



	private:
		void init();
		void release();



	public:
		void SetCursorVisibility( const bool visible );
	private:
		void setCursorVisibilityProcess( HandleT handle, const bool visible );

	public:
		void SetCursorPosition( const short x, const short y );
	private:
		void setCursorPositionProcess( HandleT handle, const short x, const short y );

	public:
		void ClearBufferColor( const short x, const short y, const int length );
	private:
		void clearBufferColorProcess( HandleT handle, const short x, const short y, const int length, const unsigned short color );



	public:
		void ClearCurrentBuffer();
	private:
		void clearBufferProcess( HandleT handle );

	public:
		void Write2BackBuffer( const r2bix_render::Texture* const texture );
	private:
		void write2BufferProcess( HandleT handle, const r2bix_render::Texture* const texture );

	public:
		void Swap();

		std::string OpenTextInputBuffer(const short x, const short y, const int length, const r2bix_render::Texture* const texture);



		//
		//
		//
		r2::Point<short> GetScreenBufferOffset() const
		{
			return mScreenBufferOffset;
		}



	private:
		HandleT mBufferHandleOriginal;
		std::streambuf* mCoutOriginalStreamBuffer;

		HandleT mBufferHandleList[BUFFER_COUNT];
		CoutBufferRedirector mCoutBufferRedirectorList[BUFFER_COUNT];

		int mCurrentBufferIndex;

		r2::Point<short> mScreenBufferOffset;
	};
}