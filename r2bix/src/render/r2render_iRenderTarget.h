#pragma once

#include <stdint.h>

#include "r2/r2_RectInt.h"

namespace r2render
{
	class iRenderTarget
	{
	public:
		virtual void FillAll( const char c ) = 0;
		virtual void Fill( const uint32_t x, const uint32_t y, const char c ) = 0;

		virtual r2::RectInt GetRect() const = 0;
	};
}