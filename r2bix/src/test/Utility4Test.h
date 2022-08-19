#pragma once

#include "r2/r2_Rect_Int.h"

namespace r2render
{
	class Texture;
	class TextureFrame;
}

class Utility4Test
{
private:
	Utility4Test() = delete;

public:
	static void DrawTexture( const r2render::Texture& texture );
	static void DrawTextureCharacter( const r2render::Texture& texture );
	static void DrawTextureColor( const r2render::Texture& texture );
	static void DrawTextureDisuse( const r2render::Texture& texture );

	static void DrawTextureFrame( const r2render::TextureFrame& frame );
};