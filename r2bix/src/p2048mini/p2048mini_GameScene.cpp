#include "pch.h"
#include "p2048mini_GameScene.h"

#include <cassert>
#include <conio.h>
#include <numeric>

#include "base/r2base_Director.h"
#include "component/r2component_CustomTextureComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "node/r2node_CustomTextureNode.h"
#include "node/r2node_PivotNode.h"

#include "p2048mini/p2048mini_Stage.h"
#include "p2048mini/p2048mini_StageViewComponent.h"
#include "p2048mini/p2048mini_StageViewNode.h"
#include "p2048mini/p2048minitable_TextureTable.h"

namespace p2048mini
{
	GameScene::GameScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mStep( eStep::Make2Number )
		, mStage( 4u, 4u )
		, mStageViewComponent( nullptr )
	{}

	r2node::SceneNodeUp GameScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) GameScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool GameScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		//
		// Table Load
		//
		p2048minitable::TextureTable::GetInstance().Load();

		//
		// Background
		//
		{
			auto node = AddChild<r2node::CustomTextureNode>();
			node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->Reset( 37, 17, '=' );
			node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
			node->GetComponent<r2component::TextureRenderComponent>()->ResetVisibleRect();

			node->mTransformComponent->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f ) - ( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( node->GetComponent<r2component::CustomTextureComponent>()->GetTexture()->GetHeight() * 0.5f )
			);
		}

		//
		// Stage
		//
		{
			auto stage_view_node = AddChild<p2048mini::StageViewNode>( 1 );

			mStageViewComponent = stage_view_node->GetComponent<p2048mini::StageViewComponent>();
			mStageViewComponent->Setup( &mStage );

			stage_view_node->GetComponent<r2component::TransformComponent>()->SetPosition(
				( mDirector.GetScreenBufferSize().GetWidth() * 0.5f ) - ( mStageViewComponent->GetWidth() * 0.5f )
				, ( mDirector.GetScreenBufferSize().GetHeight() * 0.5f ) - ( mStageViewComponent->GetHeight() * 0.5f )
			);
		}

		//
		// Debug
		//
		{
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() - 1, 0 );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() - 1, mDirector.GetScreenBufferSize().GetHeight() - 1 );
			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( 0, mDirector.GetScreenBufferSize().GetHeight() - 1 );

			AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() )->mTransformComponent->SetPosition( mDirector.GetScreenBufferSize().GetWidth() * 0.5f, mDirector.GetScreenBufferSize().GetHeight() * 0.5f );
		
		}

		return true;
	}
	void GameScene::Update( const float delta_time )
	{
		switch( mStep )
		{
		case eStep::GameReady:
			// Make Number
			break;
		case eStep::GameStart:
			// Show Stage, On Input
			break;
		case eStep::GameUpdate:
			// Input Process, Game End Check
			break;
		case eStep::GameEnd:
			// Do Something
			break;
		}

		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input ) // ESC
			{
				mDirector.RequestAbort();
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}