#include "pmr_CompanyScene.h"

#include <conio.h>

#include "r2bix/r2base_Director.h"
#include "r2bix/r2component_LabelComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2node_LabelSNode.h"

namespace pmr
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2node::SceneNode( director )
	{}

	r2node::SceneNodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		{
			auto node = AddChild<r2node::LabelNode>();
			node->GetComponent<r2component::LabelComponent>()->SetString( CompanyScene::GetTitle() );
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