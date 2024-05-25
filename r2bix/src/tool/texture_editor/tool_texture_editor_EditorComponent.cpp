#include "tool_texture_editor_EditorComponent.h"

#include "r2bix_Director.h"

#include "r2bix_node_Node.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_UIControlComponent.h"

namespace tool_texture_editor
{
	EditorComponent::EditorComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<EditorComponent>( director, owner_node )
		, mFileName()
		, mSlot4KeyResponse( [this]( int, r2bix_ui::eKeyStatus )->bool
		{
			//
			// Do Something
			//

			auto texture_node = mCanvasNode->GetChildByName( "texture" );

			auto fill_point = GetDirector().GetInputManager().GetCursorPoint();

			auto texture_world_position = texture_node->mTransformComponent->GetWorldPosition();

			fill_point.Minus( texture_world_position.GetX(), texture_world_position.GetY() );
			
			texture_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillCharacter( fill_point.GetX(), fill_point.GetY(), '+' );

			return true;
		} )
		, mCanvasNode( nullptr )
	{}



	void EditorComponent::SetFileName( const std::string_view str )
	{
		mFileName = str;

		auto file_name_view_node = GetOwnerNode().GetChildByName( "file_name_view" );
		if( file_name_view_node )
		{
			file_name_view_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( str );
		}
	}



	void EditorComponent::SetCanvas( r2bix_node::Node* canvas_node )
	{
		mCanvasNode = canvas_node;
		mCanvasNode->GetComponent<r2bix_component::UIControlComponent>()->ConnectSlot4KeyResponse( &mSlot4KeyResponse );
	}
}