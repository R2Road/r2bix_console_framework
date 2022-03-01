#include "pch.h"
#include "p2048_CompanyScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "component/r2component_TransformComponent.h"
#include "render/r2render_iRenderable.h"

#include "scene/DevelopScene.h"

namespace r2component
{
	class TextRenderComponent : public r2base::Component
	{
	private:
		TextRenderComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
			, mTransformComponent( nullptr )
			, mRect()
			, mTexture( " " )
		{}

	public:
		static std::unique_ptr<TextRenderComponent> Create( r2base::Node& owner_node )
		{
			std::unique_ptr<TextRenderComponent> ret( new ( std::nothrow ) TextRenderComponent( owner_node ) );
			if( !ret || !ret->Init() )
			{
				ret.reset();
			}

			return ret;
		}

		//
		//
		//
		r2::RectInt GetRect() const { return mRect; }
		const r2render::Texture& GetTexture() const { return mTexture; }

		//
		//
		//
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mRect.Set( x, y, width, height );
		}
		void SetString( const std::string_view str )
		{
			mTexture.Reset( str );
		}

	public:
		r2component::TransformComponent* mTransformComponent;
	private:
		r2::RectInt mRect;
		r2render::Texture mTexture;
	};
}

namespace r2game
{
	class LabelNode : public r2game::Node, public r2render::iRenderable
	{
	public:
		LabelNode( r2base::Director& director ) : r2game::Node( director )
			, mTransformComponent( nullptr )
			, mTextRenderComponent( nullptr )
		{}

		static std::unique_ptr<LabelNode> Create( r2base::Director& director )
		{
			std::unique_ptr<LabelNode> ret( new ( std::nothrow ) LabelNode( director ) );
			if( !ret || !ret->Init() )
			{
				ret.reset();
			}

			return ret;
		}

		//
		// Override
		//
	private:
		bool Init() override
		{
			auto transform_component = r2component::TransformComponent::Create( *this );
			mTransformComponent = transform_component.get();
			AddComponent( std::move( transform_component ) );

			auto text_render_component = r2component::TextRenderComponent::Create( *this );
			text_render_component->mTransformComponent = mTransformComponent;
			mTextRenderComponent = text_render_component.get();
			AddComponent( std::move( text_render_component ) );

			return true;
		}
	public:
		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override
		{
			//
			// World Space : My Rect : Test
			//
			{
				const r2::RectInt my_world_space_rect( mTextRenderComponent->GetRect().GetOrigin() + mTransformComponent->GetPosition(), mTextRenderComponent->GetRect().GetSize() );
				if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
				{
					return;
				}
			}

			//
			// Camera Space : My Position
			//
			const auto camera_space_my_position = mTransformComponent->GetPosition() - camera->GetPoint();

			//
			// Render Target Space : My Position
			//
			const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();

			//
			//
			//
			render_target->Fill( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), 'A' );

			//
			// Render Target Space : My Rect
			//
			auto render_target_space_my_rect = mTextRenderComponent->GetRect();
			render_target_space_my_rect.MoveOrigin( render_target_space_my_position.GetX(), render_target_space_my_position.GetY() );

			//
			// Render Target Space : Intersect Rect
			//
			auto render_target_space_intersect_rect = render_target->GetRect().IntersectsWithRect( render_target_space_my_rect );

			//
			// Offset
			//
			const auto off_set_point = render_target_space_intersect_rect.GetOrigin() - render_target_space_my_rect.GetOrigin();
			for( int y = render_target_space_intersect_rect.GetMinY(), ty = 0; render_target_space_intersect_rect.GetMaxY() > y; ++y, ++ty )
			{
				for( int x = render_target_space_intersect_rect.GetMinX(), tx = 0; render_target_space_intersect_rect.GetMaxX() > x; ++x, ++tx )
				{
					render_target->Fill(
						x, y
						, mTextRenderComponent->GetTexture().Get( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
					);
				}
			}
		}

		//
		//
		//
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mTextRenderComponent->SetRect( x, y, width, height );
		}
		void SetString( const std::string_view str )
		{
			mTextRenderComponent->SetString( str );
		}

	public:
		r2component::TransformComponent* mTransformComponent;
		r2component::TextRenderComponent* mTextRenderComponent;
	};
}

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2game::Scene( director )
		, mCamera( { 25, 25 }, { 50, 50 } )
		, mRenderTarget( 50, 50, '@' )

		, mLabelNode( nullptr )
	{}

	r2base::NodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		auto label_node = r2game::LabelNode::Create( mDirector );
		label_node->mTransformComponent->SetPosition( 5, 5 );
		label_node->SetRect( 0, 0, 30, 1 );
		label_node->SetString( "# " "2048 Game Scene" " #" );
		mLabelNode = label_node.get();
		AddChild( std::move( label_node ) );

		return true;
	}
	void CompanyScene::Update()
	{
		mLabelNode->Render( &mCamera, &mRenderTarget );

		for( int y = 0; mRenderTarget.GetHeight() > y; ++y )
		{
			std::cout << mRenderTarget.GetLine( y );
			std::cout << r2::linefeed;
		}

		auto input = _getch();
		if( 27 == input )
		{
			mDirector.Setup( DevelopScene::Create( mDirector ) );
		}

		system( "cls" );
	}
}