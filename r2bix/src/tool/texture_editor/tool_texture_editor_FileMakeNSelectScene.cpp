#include "tool_texture_editor_FileMakeNSelectScene.h"

#include "r2bix_ColorValue.h"
#include "r2bix_Director.h"

#include "r2bix_component_HollowRectComponent.h"
#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_RectComponent.h"
#include "r2bix_component_TransformComponent.h"
#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UISimpleButtonComponent.h"
#include "r2bix_component_UITextFieldComponent.h"

#include "r2bix_node_HollowRectNode.h"
#include "r2bix_node_LabelSNode.h"
#include "r2bix_node_RectNode.h"
#include "r2bix_node_UIPannelNode.h"
#include "r2bix_node_UISimpleButtonNode.h"
#include "r2bix_node_UITextFieldNode.h"

#include "tool_texture_editor_EditorComponent.h"
#include "tool_texture_editor_EditorScene.h"

namespace tool_texture_editor
{
	r2bix_node::NodeUp FileMakeNSelectScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// Background
			//
			{
				auto node = ret->AddChild<r2bix_node::HollowRectNode>();
				node->mTransformComponent->SetPivot( 0.f, 0.f );
				node->GetComponent<r2bix_component::HollowRectComponent>()->Set(
					  director.GetScreenSize().GetWidth()
					, director.GetScreenSize().GetHeight()
					, '#'
					, ' '
				);
			}
			//
			// Exit
			//
			{
				auto component = ret->AddComponent<r2bix_component::InputKeyboardComponent>();
				component->SetCallback(
					r2bix_input::eKeyCode::VK_ESCAPE
					, [&director]( r2bix_input::eKeyStatus s )->bool
				{
					if( r2bix_input::eKeyStatus::Push == s )
					{
						director.RequestAbort();
						return true;
					}

					return false;
				}
				);
				component->Activate();
			}





			//
			// Main Menu
			//
			{
				//
				// Pannel
				//
				auto pn_node = ret->AddChild<r2bix_node::UIPannelNode>();
				{
					pn_node->mTransformComponent->SetPosition( 28, 12 );
					pn_node->mTransformComponent->SetPivot( 0.f, 0.f );
					pn_node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 50, 15 );
					{
						auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
						rect_node->mTransformComponent->SetPivot( 0.f, 0.f );
						rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
							  pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
							, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
							, ' '
							, r2bix::eBackgroundColor::BG_Gray
						);
					}
				}

				//
				// Button
				//
				{
					auto button_node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					button_node->mTransformComponent->SetPosition( 5, 3 );
					button_node->mTransformComponent->SetPivot( 0.f, 0.f );
					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 40, 3 );
					{
						auto label_node = button_node->AddChild<r2bix_node::LabelSNode>();
						label_node->mTransformComponent->SetPosition( 20, 1 );
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "N E W" );
					}

					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->SetCallback4KeyResponse(
						[root = ret.get()]( int i , r2bix_ui::eKeyStatus s )->bool
						{
							if( 0 == i && r2bix_ui::eKeyStatus::Push == s )
							{
								auto node = root->GetChildByName( "new" );
								if( node )
								{
									node->SetVisible( true );
								}

								return true;
							}
							
							return true;
						}
					);
				}

				{
					auto button_node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					button_node->mTransformComponent->SetPosition( 5, 9 );
					button_node->mTransformComponent->SetPivot( 0.f, 0.f );
					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 40, 3 );
					{
						auto label_node = button_node->AddChild<r2bix_node::LabelSNode>();
						label_node->mTransformComponent->SetPosition( 20, 1 );
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "O P E N" );
					}
				}
			}



			//
			// New
			//
			{
				//
				// Pannel
				//
				auto pn_node = ret->AddChild<r2bix_node::UIPannelNode>();
				pn_node->SetName( "new" );
				{
					pn_node->mTransformComponent->SetPosition( 28, 12 );
					pn_node->mTransformComponent->SetPivot( 0.f, 0.f );
					pn_node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 50, 15 );
					{
						auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
						rect_node->mTransformComponent->SetPivot( 0.f, 0.f );
						rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
							  pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
							, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
							, ' '
							, r2bix::eBackgroundColor::BG_Gray
						);
					}
				}
				pn_node->SetVisible( false );

				//
				// File Name
				//
				{
					auto label_node = pn_node->AddChild<r2bix_node::LabelSNode>();
					label_node->mTransformComponent->SetPosition( 17, 3 );
					label_node->mTransformComponent->SetPivot( 1.f, 0.f );
					label_node->GetComponent<r2bix_component::LabelSComponent>()->Set( "Name :", r2bix::eBackgroundColor::BG_Gray | r2bix::eBackgroundColor::BG_Black );

					auto node = pn_node->AddChild<r2bix_node::UITextFieldNode>();
					node->SetName( "file_name" );
					node->mTransformComponent->SetPosition( 19, 3 );
					node->mTransformComponent->SetPivot( 0.f, 0.f );
					node->GetComponent<r2bix_component::UITextFieldComponent>()->Set( 20, "new_file~~~~~~~~~~~!" );
				}

				//
				// Width
				//
				{
					auto label_node = pn_node->AddChild<r2bix_node::LabelSNode>();
					label_node->mTransformComponent->SetPosition( 17, 5 );
					label_node->mTransformComponent->SetPivot( 1.f, 0.f );
					label_node->GetComponent<r2bix_component::LabelSComponent>()->Set( "Width :", r2bix::eBackgroundColor::BG_Gray | r2bix::eBackgroundColor::BG_Black );

					auto node = pn_node->AddChild<r2bix_node::UITextFieldNode>();
					node->SetName( "file_width" );
					node->mTransformComponent->SetPosition( 19, 5 );
					node->mTransformComponent->SetPivot( 0.f, 0.f );
					node->GetComponent<r2bix_component::UITextFieldComponent>()->Set( 3, "80" );
				}

				//
				// Height
				//
				{
					auto label_node = pn_node->AddChild<r2bix_node::LabelSNode>();
					label_node->mTransformComponent->SetPosition( 17, 7 );
					label_node->mTransformComponent->SetPivot( 1.f, 0.f );
					label_node->GetComponent<r2bix_component::LabelSComponent>()->Set( "Height :", r2bix::eBackgroundColor::BG_Gray | r2bix::eBackgroundColor::BG_Black );

					auto node = pn_node->AddChild<r2bix_node::UITextFieldNode>();
					node->SetName( "file_height" );
					node->mTransformComponent->SetPosition( 19, 7 );
					node->mTransformComponent->SetPivot( 0.f, 0.f );
					node->GetComponent<r2bix_component::UITextFieldComponent>()->Set( 3, "40" );
				}

				//
				// Generate
				//
				{
					auto node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					node->mTransformComponent->SetPosition( 15, 10 );
					node->mTransformComponent->SetPivot( 0.5f, 0.5f );
					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 10, 3 );
					{
						auto label_node = node->AddChild<r2bix_node::LabelSNode>();
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Generate" );
					}

					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->SetCallback4KeyResponse(
						[root = ret.get()]( int i, r2bix_ui::eKeyStatus s )->bool
						{
							if( 0 == i && r2bix_ui::eKeyStatus::Push == s )
							{
								auto file_name_node = root->GetChildByName( "file_name" );
								auto file_width_node = root->GetChildByName( "file_width" );
								auto file_height_node = root->GetChildByName( "file_height" );
								if( file_name_node && file_width_node && file_height_node )
								{
									if( !file_name_node->GetComponent<r2bix_component::UITextFieldComponent>()->GetText().empty() )
									{
										int file_width = 0;
										int file_height = 0;

										try
										{
											file_width = std::stoi( file_width_node->GetComponent<r2bix_component::UITextFieldComponent>()->GetText() );
											file_height = std::stoi( file_height_node->GetComponent<r2bix_component::UITextFieldComponent>()->GetText() );
										}
										catch( std::invalid_argument const& )
										{}
										catch( std::out_of_range const& )
										{}

										if( 0 < file_width && 0 < file_height )
										{
											auto next_scene = tool_texture_editor::EditorScene::Create( root->GetDirector() );

											next_scene->GetComponent< tool_texture_editor::EditorComponent>()->SetFileInformation(
												  file_name_node->GetComponent<r2bix_component::UITextFieldComponent>()->GetText()
												, file_width, file_height
											);
											root->GetDirector().Setup( std::move( next_scene ) );
										}
									}
								}

								return true;
							}

							return true;
						}
					);
				}

				//
				// Cancel
				//
				{
					auto node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					node->mTransformComponent->SetPosition( 35, 10 );
					node->mTransformComponent->SetPivot( 0.5f, 0.5f );
					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 10, 3 );
					{
						auto label_node = node->AddChild<r2bix_node::LabelSNode>();
						label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Cancel" );
					}

					node->GetComponent<r2bix_component::UISimpleButtonComponent>()->SetCallback4KeyResponse(
						[root = ret.get()]( int i, r2bix_ui::eKeyStatus s )->bool
						{
							if( 0 == i && r2bix_ui::eKeyStatus::Push == s )
							{
								auto node = root->GetChildByName( "new" );
								if( node )
								{
									node->SetVisible( false );
								}

								return true;
							}

							return true;
						}
					);
				}
			}
		}

		return ret;
	}
}