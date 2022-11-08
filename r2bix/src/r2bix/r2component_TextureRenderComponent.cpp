#include "r2component_TextureRenderComponent.h"

#include "r2base_Node.h"
#include "r2bix_DebugConfig.h"
#include "r2component_TransformComponent.h"
#include "r2render_Camera.h"
#include "r2render_Texture.h"

namespace r2component
{
	TextureRenderComponent::TextureRenderComponent( r2bix_node::Node& owner_node ) : r2base::Component<TextureRenderComponent>( owner_node )
		, mPivotPoint( 0.5f, 0.5f )
		, mVisibleRect()
		, mTexture( nullptr )
		, mColorMaskOption( r2base::eColorMaskFlag::CMF_Foreground | r2base::eColorMaskFlag::CMF_Background )
	{}

	void TextureRenderComponent::Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target, r2::PointInt offset )
	{
		if( !mTexture )
		{
			return;
		}

		//
		// World Space : My Rect : Test
		//
		{
			const r2::RectInt my_world_space_rect( offset + mVisibleRect.GetOrigin() + mOwnerNode.mTransformComponent->GetPosition(), mVisibleRect.GetSize() );
			if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
			{
				return;
			}
		}

		//
		// Camera Space : My Position
		//
		const auto camera_space_my_position = offset + mOwnerNode.mTransformComponent->GetPosition() - camera->GetPoint();

		//
		// Render Target Space : My Position
		//
		const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();

		//
		// Render Target Space : My Rect
		//
		auto render_target_space_my_rect = mVisibleRect;
		render_target_space_my_rect.MoveOrigin( render_target_space_my_position.GetX(), render_target_space_my_position.GetY() );

		//
		// Render Target Space : Intersect Rect
		//
		auto render_target_space_intersect_rect = render_target->GetRect().IntersectsWithRect( render_target_space_my_rect );

		//
		// Offset
		//
		const auto off_set_point = render_target_space_intersect_rect.GetOrigin() - render_target_space_my_rect.GetOrigin();
		for( int y = render_target_space_intersect_rect.GetMinY(), ty = 0; render_target_space_intersect_rect.GetMaxY() >= y; ++y, ++ty )
		{
			for( int x = render_target_space_intersect_rect.GetMinX(), tx = 0; render_target_space_intersect_rect.GetMaxX() >= x; ++x, ++tx )
			{
				if( !mTexture->GetCharacterDisuse( off_set_point.GetX() + tx, off_set_point.GetY() + ty ) )
				{
					render_target->FillCharacter(
						x, y
						, mTexture->GetCharacter( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
					);
				}

				render_target->FillColorWithMask(
					x, y
					, mTexture->GetColor( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
					, mColorMaskOption
				);
			}
		}

		//
		// Debug
		//
		if( r2bix::DebugConfig::GetLabelConfig().bShowPositionPivot )
		{
			render_target->FillCharacter( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), '+' );
		}
	}

	void TextureRenderComponent::SetPivotPoint( const float x, const float y )
	{
		mPivotPoint.Set( x, y );

		ResetVisibleRect();
	}
	void TextureRenderComponent::SetTexture( const r2render::Texture* const texture )
	{
		mTexture = texture;

		ResetVisibleRect();
	}
	void TextureRenderComponent::ResetVisibleRect()
	{
		if( !mTexture )
		{
			return;
		}

		mVisibleRect.Set(
			-static_cast<int>( mTexture->GetWidth() * mPivotPoint.GetX() )
			, -static_cast<int>( mTexture->GetHeight() * mPivotPoint.GetY() )
			, mTexture->GetWidth() - 1
			, mTexture->GetHeight() - 1
		);
	}
}