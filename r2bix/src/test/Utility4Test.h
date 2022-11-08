#pragma once

#include "r2/r2_RectInt.h"

namespace r2bix_render
{
	class Texture;
	class TextureFrame;
}

class Utility4Test
{
private:
	Utility4Test() = delete;

public:
	static void DrawTexture( const r2bix_render::Texture& texture );
	static void DrawTextureCharacter( const r2bix_render::Texture& texture );
	static void DrawTextureColor( const r2bix_render::Texture& texture );
	static void DrawTextureDisuse( const r2bix_render::Texture& texture );

	static void DrawTextureFrame( const r2bix_render::TextureFrame& frame );
};