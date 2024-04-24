#pragma once

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
		void setCursorVisibility( const bool visible );

	public:
		void InitCursor();
		void ClearCurrentBuffer();
		void Write2BackBuffer( const r2bix_render::Texture* const texture );
		void Swap();

	private:
		HandleT mBufferHandleOriginal;
		std::streambuf* mCoutOriginalStreamBuffer;

		HandleT mBufferHandleList[BUFFER_COUNT];
		CoutBufferRedirector mCoutBufferRedirectorList[BUFFER_COUNT];

		int mCurrentBufferIndex;

		r2::Point<short> mScreenBufferOffset;
	};
}