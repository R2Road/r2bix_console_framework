#include "pch.h"
#include "r2render_TextureFrame.h"

namespace r2render
{
	TextureFrame::TextureFrame( const Texture* const texture ) :
		mTexture( texture )
		, mVisibleRect( 0, 0, texture->GetWidth(), texture->GetHeight() )
	{}

	Texture::ValueT TextureFrame::Get( const uint32_t x, const uint32_t y ) const
	{
		const auto target_x = x + mVisibleRect.GetOrigin().GetX();
		const auto target_y = y + mVisibleRect.GetOrigin().GetY();

		return mTexture->Get( target_x, y + target_y );
	}
}