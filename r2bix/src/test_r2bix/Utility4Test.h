#pragma once

#include "r2/r2_RectInt.h"

namespace r2render
{
	class TextureFrame;
}

class Utility4Test
{
private:
	Utility4Test() = delete;

public:
	static void DrawRect( const int offset_y, const r2::RectInt& rect, const char c );
	static void DrawRectInfo_Min_Max( const r2::RectInt& rect );

	static void DrawTextureFrame( const r2render::TextureFrame& frame );
};