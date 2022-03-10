#include "pch.h"
#include "r2node_SpriteNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TextureFrameRenderComponent.h"

namespace r2node
{
	r2base::NodeUp SpriteNode::Create( r2base::Director& director, r2render::TextureFrame* const texture_frame )
	{
		auto ret( r2base::Node::Create( director ) );
		if( ret )
		{
			ret->AddComponent<r2component::TextureFrameRenderComponent>();
			ret->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( texture_frame );
		}

		return ret;
	}
}