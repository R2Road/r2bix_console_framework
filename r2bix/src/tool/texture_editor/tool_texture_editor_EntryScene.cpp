#include "tool_texture_editor_EntryScene.h"

#include "r2bix_Director.h"

#include "r2bix_component_LabelSComponent.h"

#include "r2bix_node_LabelSNode.h"

#include "tool_texture_editor_FileMakeNSelectScene.h"

namespace tool_texture_editor
{
	class EntrySceneComponent : public r2bix_component::Component<EntrySceneComponent>
	{
	public:
		EntrySceneComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<EntrySceneComponent>( director, owner_node ) {}


		//
		// Override
		//
		void updateProcess( const float ) override
		{
			//
			// Load Resources
			//
			{
				// Do Something
			}

			//
			//
			//
			GetDirector().Setup( tool_texture_editor::FileMakeNSelectScene::Create( GetDirector() ) );
		}
	};

	r2bix_node::NodeUp EntryScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			//
			//
			//
			{
				auto node = ret->AddChild<r2bix_node::LabelSNode>();
				node->GetComponent<r2bix_component::LabelSComponent>()->SetString( EntryScene::GetTitle() );
				node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					  director.GetScreenSize().GetWidth() * 0.5f
					, director.GetScreenSize().GetHeight() * 0.5f
				);
			}

			//
			//
			//
			{
				ret->AddComponent<EntrySceneComponent>();
			}
		}

		return ret;
	}
}