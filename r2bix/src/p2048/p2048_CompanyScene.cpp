#include "pch.h"
#include "p2048_CompanyScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureFrameAnimationComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "node/r2node_LabelNode.h"
#include "node/r2node_SpriteAnimationNode.h"

#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mLabelNode( nullptr )
		, mSpriteAnimationNode( nullptr )
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
			mLabelNode = AddChild<r2node::LabelNode>();

			mLabelNode->GetComponent<r2component::TextureRenderComponent>()->SetRect( 0, 0, 30, 0 );
			mLabelNode->GetComponent<r2component::LabelComponent>()->SetStringWithResize( "# " "R2Road Studio" " #" );

			mLabelNode->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.6f
			);
		}

		//
		// Logo
		//
		{
			mSpriteAnimationNode = AddChild<r2node::SpriteAnimationNode>();

			mSpriteAnimationNode->GetComponent<r2component::TextureFrameAnimationComponent>()->LoadAnimation(
				p2048table::TextureFrameAnimationTable::GetInstance().Get( 1 )
			);
			mSpriteAnimationNode->GetComponent<r2component::TextureFrameAnimationComponent>()->RunAnimation( r2animation::eIndex::Run_1 );

			mSpriteAnimationNode->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.35f
			);
		}

		return true;
	}
	void CompanyScene::Update( const float delta_time )
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input )
			{
				mDirector.RequestAbort();
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}