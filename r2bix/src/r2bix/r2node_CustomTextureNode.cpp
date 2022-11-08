#include "r2node_CustomTextureNode.h"

#include <numeric>

#include "r2bix_Director.h"
#include "r2component_CustomTextureComponent.h"
#include "r2component_TextureRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp CustomTextureNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			//
			//
			//
			{
				auto custome_texture_component = ret->AddComponent<r2component::CustomTextureComponent>();
				auto texture_render_component = ret->AddComponent<r2component::TextureRenderComponent>();

				texture_render_component->SetTexture( custome_texture_component->GetTexture() );
			}
		}

		return ret;
	}
}