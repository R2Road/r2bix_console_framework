#include "p2048_CompanyScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "r2bix/r2base_Director.h"
#include "r2bix/r2component_LabelComponent.h"
#include "r2bix/r2component_TextureFrameAnimationComponent.h"
#include "r2bix/r2component_TextureFrameRenderComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2component_TransformComponent.h"
#include "r2bix/r2node_LabelSNode.h"
#include "r2bix/r2node_SpriteAnimationNode.h"

#include "p2048_TitleScene.h"
#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mChangeSceneTimer( 2.f, true )
	{}

	r2node::SceneNodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		//
		// Company Name
		//
		{
			auto label_node = AddChild<r2node::LabelSNode>();

			label_node->GetComponent<r2component::LabelSComponent>()->SetString( "R2Road Studio" );

			label_node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.62f
			);
		}

		//
		// Logo
		//
		{
			auto sprite_animation_node = AddChild<r2node::SpriteAnimationNode>( 1 );

			sprite_animation_node->GetComponent<r2component::TextureFrameAnimationComponent>()->LoadAnimation(
				p2048table::TextureFrameAnimationTable::GetInstance().Get( 1 )
			);
			sprite_animation_node->GetComponent<r2component::TextureFrameAnimationComponent>()->RunAnimation_Repeat( r2animation::eIndex::Run_1 );

			sprite_animation_node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.42f
			);
		}

		return true;
	}
	void CompanyScene::Update( const float delta_time )
	{
		if( !mChangeSceneTimer.update( delta_time ) )
		{
			mDirector.Setup( p2048::TitleScene::Create( mDirector ) );
		}
		else
		{
			if( _kbhit() )
			{
				auto input = _getch();
				if( 27 == input ) // ESC
				{
					mDirector.RequestAbort();
				}
				else if( 32 == input ) // Space
				{
					mDirector.Setup( p2048::TitleScene::Create( mDirector ) );
				}
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}