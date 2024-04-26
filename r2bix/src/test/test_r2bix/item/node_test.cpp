#include "node_test.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_InputComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_LabelMComponent.h"
#include "r2bix_component_RectComponent.h"
#include "r2bix_component_TextureFrameAnimationComponent.h"
#include "r2bix_component_TextureFrameRenderComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_TransformComponent.h"
#include "r2bix_component_UIButtonComponent.h"
#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UIPannelComponent.h"
#include "r2bix_node_CustomTextureNode.h"
#include "r2bix_node_LabelSNode.h"
#include "r2bix_node_LabelMNode.h"
#include "r2bix_node_PivotNode.h"
#include "r2bix_node_RectNode.h"
#include "r2bix_node_SpriteAnimationNode.h"
#include "r2bix_node_SpriteNode.h"
#include "r2bix_node_UIButtonNode.h"
#include "r2bix_node_UIPannelNode.h"
#include "r2bix_helper/r2bix_helper_Printer4Texture.h"

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace node_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Child_Count::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Child : Count";
		};
	}
	r2tm::DoFunctionT Child_Count::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

			LS();

			{
				EXPECT_EQ( 0, dummy_node->GetChildCount() );

				LF();

				EXPECT_NE( nullptr, dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( 1, dummy_node->GetChildCount() );

				LF();

				EXPECT_NE( nullptr, dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( 2, dummy_node->GetChildCount() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Child_Sequence::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Child : Sequence";
		};
	}
	r2tm::DoFunctionT Child_Sequence::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Z값이 큰 노드가 목록의 뒤쪽으로 자리한다." << r2tm::linefeed2;

				DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				LF();

				DECLARATION_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>( 1 ) );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECLARATION_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>( 0 ) );
				EXPECT_EQ( child_2, ( *dummy_node->GetChildContainer().begin() ).get() );
			}

			LS();

			{
				std::cout << r2tm::tab << "+ 동일한 Z의 노드가 이미 있다면 새로 추가된 노드는 같은 Z를 가진 노드 군의 가장 마지막에 자리한다." << r2tm::linefeed2;

				DECLARATION_MAIN( const auto dummy_node = r2bix_node::Node::Create( dummy_director ) );

				LF();

				DECLARATION_MAIN( auto child_1 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECLARATION_MAIN( auto child_2 = dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_1, ( *dummy_node->GetChildContainer().begin() ).get() );

				LF();

				DECLARATION_MAIN( dummy_node->AddChild<r2bix_node::Node>() );
				EXPECT_EQ( child_2, ( *( ++dummy_node->GetChildContainer().begin() ) ).get() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT LabelS::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label S";
		};
	}
	r2tm::DoFunctionT LabelS::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::LabelSNode::Create( dummy_director ) );

			LS();

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::CustomTextureComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::LabelSComponent>() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT LabelM::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label M";
		};
	}
	r2tm::DoFunctionT LabelM::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::LabelMNode::Create( dummy_director ) );

			LS();

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::CustomTextureComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::LabelMComponent>() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT Sprite::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite";
		};
	}
	r2tm::DoFunctionT Sprite::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::SpriteNode::Create( dummy_director ) );

			LS();

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT SpriteAnimation::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Sprite Animation";
		};
	}
	r2tm::DoFunctionT SpriteAnimation::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( const auto dummy_node = r2bix_node::SpriteAnimationNode::Create( dummy_director ) );

			LS();

			{
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TransformComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
				EXPECT_TRUE( dummy_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );

				LF();

				DECLARATION_MAIN( auto frame = dummy_node->GetComponent<r2bix_component::TextureFrameRenderComponent>() );
				DECLARATION_MAIN( auto animation = dummy_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>() );
				EXPECT_EQ( frame, animation->GetTextureFrameRenderComponent() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CustomeTexture::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Custome Texture Node";
		};
	}
	r2tm::DoFunctionT CustomeTexture::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 13, 5 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( auto node = r2bix_node::CustomTextureNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TransformComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TextureRenderComponent>() );

			LS();

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 3, 3, 'T' ) );
				PROCESS_MAIN( node->GetComponent<r2bix_component::TextureRenderComponent>()->ResetVisibleRect() );

				LF();

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 5, 5, 'S' ) );
				PROCESS_MAIN( node->GetComponent<r2bix_component::TextureRenderComponent>()->ResetVisibleRect() );

				LF();

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}






	r2tm::TitleFunctionT UIPannel_ComponentCheck::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIPannel : Component Check";
		};
	}
	r2tm::DoFunctionT UIPannel_ComponentCheck::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 13, 5 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( auto node = r2bix_node::UIPannelNode::Create( dummy_director ) );
			EXPECT_TRUE( nullptr != node->GetComponent<r2bix_component::TransformComponent>() );
			EXPECT_TRUE( nullptr != node->GetComponent<r2bix_component::UIPannelComponent>() );
			EXPECT_TRUE( nullptr != node->GetComponent<r2bix_component::UIControlComponent>() );

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT UIPannel_CursorResponse::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIPannel : Cursor Response";
		};
	}
	r2tm::DoFunctionT UIPannel_CursorResponse::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			r2bix::Director director( { 51, 51, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );

			//
			// Scene
			//
			r2bix_node::Node* scene;
			{
				auto temp = r2bix_node::Node::Create( director );
				scene = temp.get();

				director.Setup( std::move( temp ) );

				auto input_component = scene->AddComponent<r2bix_component::InputComponent>();
				input_component->SetKeyboardCallback( r2bix_input::eKeyCode::VK_ESCAPE, [&director]( r2bix_input::eKeyStatus )->bool
				{
					director.RequestAbort();

					return false;
				} );

				input_component->Activate();
			}

			//
			// Background
			//
			{
				auto node = scene->AddChild<r2bix_node::CustomTextureNode>();
				node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 50, 50, '#', r2bix::ColorValue( r2bix::eBackgroundColor::BG_Gray ) );
				node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
			}

			//
			// Pannel
			//
			{
				// Pannel 1
				{
					auto node = scene->AddChild<r2bix_node::UIPannelNode>();

					// Debug Area View
					auto rect_node = node->AddChild<r2bix_node::RectNode>();
					rect_node->GetComponent<r2bix_component::RectComponent>()->Set( r2::Vector2{ 0.f, 0.f }, 8, 4, '1' );

					node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 8, 4 );
					node->GetComponent<r2bix_component::UIControlComponent>()->SetCallback4CursorResponse( [rect_node]( r2bix_ui::eCursorStatus s )
					{
						switch( s )
						{
						case r2bix_ui::eCursorStatus::CursorOver:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
							break;
						case r2bix_ui::eCursorStatus::CursorMove:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
							break;
						case r2bix_ui::eCursorStatus::CursorLeave:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
							break;
						}
					} );

					node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 1, 1 );
				}

				// Pannel 2
				{
					auto node = scene->AddChild<r2bix_node::UIPannelNode>();

					// Debug Area View
					auto rect_node = node->AddChild<r2bix_node::RectNode>();
					rect_node->GetComponent<r2bix_component::RectComponent>()->Set( r2::Vector2{ 0.f, 0.f }, 8, 4, '2' );

					node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 8, 4 );
					node->GetComponent<r2bix_component::UIControlComponent>()->SetCallback4CursorResponse( [rect_node]( r2bix_ui::eCursorStatus s )
					{
						switch( s )
						{
						case r2bix_ui::eCursorStatus::CursorOver:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
							break;
						case r2bix_ui::eCursorStatus::CursorMove:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
							break;
						case r2bix_ui::eCursorStatus::CursorLeave:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
							break;
						}
					} );

					node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 5, 5 );
				}

				// Pannel 3
				{
					auto node = scene->AddChild<r2bix_node::UIPannelNode>();

					// Debug Area View
					auto rect_node = node->AddChild<r2bix_node::RectNode>();
					rect_node->GetComponent<r2bix_component::RectComponent>()->Set( r2::Vector2{ 0.f, 0.f }, 8, 4, '3' );

					node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 8, 4 );
					node->GetComponent<r2bix_component::UIControlComponent>()->SetCallback4CursorResponse( [rect_node]( r2bix_ui::eCursorStatus s )
					{
						switch( s )
						{
						case r2bix_ui::eCursorStatus::CursorOver:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
							break;
						case r2bix_ui::eCursorStatus::CursorMove:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
							break;
						case r2bix_ui::eCursorStatus::CursorLeave:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
							break;
						}
					} );

					node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 3, 3 );
				}

				// Pannel 4
				{
					auto node = scene->AddChild<r2bix_node::UIPannelNode>();

					// Debug Area View
					auto rect_node = node->AddChild<r2bix_node::RectNode>();
					rect_node->GetComponent<r2bix_component::RectComponent>()->Set( r2::Vector2{ 0.f, 0.f }, 15, 6, " Key Test" );

					node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 15, 6 );
					node->GetComponent<r2bix_component::UIControlComponent>()->SetCallback4KeyResponse( [rect_node]( const int, const r2bix_ui::eKeyStatus s )->bool
					{
						switch( s )
						{
						case r2bix_ui::eKeyStatus::Push:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
							break;
						case r2bix_ui::eKeyStatus::Pressed:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
							break;
						case r2bix_ui::eKeyStatus::Release:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
							break;
						case r2bix_ui::eKeyStatus::Cancel:
							rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightAqua );
							break;
						}

						return true;
					} );

					node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 20, 3 );
				}
			}

			//
			// Process
			//
			director.Run();

			//
			// Terminate
			//
			director.Terminate();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT UIButton::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIButton";
		};
	}
	r2tm::DoFunctionT UIButton::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 13, 5 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( auto node = r2bix_node::UIButtonNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TransformComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::UIButtonComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::UIControlComponent>() );

			LS();

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 3, 3 ) );

				LF();

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 5, 4 ) );

				LF();

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT UIButton_CursorResponse::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "UIButton : Cursor Response";
		};
	}
	r2tm::DoFunctionT UIButton_CursorResponse::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			r2bix::Director director( { 51, 51, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );

			//
			// Scene
			//
			r2bix_node::Node* scene;
			{
				auto temp = r2bix_node::Node::Create( director );
				scene = temp.get();

				director.Setup( std::move( temp ) );

				auto input_component = scene->AddComponent<r2bix_component::InputComponent>();
				input_component->SetKeyboardCallback( r2bix_input::eKeyCode::VK_ESCAPE, [&director]( r2bix_input::eKeyStatus )->bool
				{
					director.RequestAbort();

					return false;
				} );

				input_component->Activate();
			}

			//
			// Background
			//
			{
				auto node = scene->AddChild<r2bix_node::CustomTextureNode>();
				node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 50, 50, '#', r2bix::ColorValue( r2bix::eBackgroundColor::BG_Gray ) );
				node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
			}

			//
			// Button Node Test
			//
			{
				//
				// Button 1 : Listener Add Failed Test
				//
				{
					auto btn_node = scene->AddChild<r2bix_node::UIButtonNode>();
					btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
					btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 10, 3 );
				}

				//
				// Button 2 : Listener Add Failed Test
				//
				{
					auto node_1 = scene->AddChild<r2bix_node::Node>();

					auto node_2 = node_1->AddChild<r2bix_node::Node>();

					auto btn_node = node_2->AddChild<r2bix_node::UIButtonNode>();
					btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
					btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 16, 6 );
				}

				//
				// Button 3 : Listener Add Success Test + Pannel Size 0
				//
				{
					auto pn_node = scene->AddChild<r2bix_node::UIPannelNode>();

					auto btn_node = pn_node->AddChild<r2bix_node::UIButtonNode>();
					btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
					btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 22, 9 );
				}

				//
				// Button 4 : Listener Add Success Test + Valid Pannel Size
				//
				{
					auto pn_node = scene->AddChild<r2bix_node::UIPannelNode>();
					pn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 28, 12 );
					pn_node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 15, 7 );
					{
						auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
						rect_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
						rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
							pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
							, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
							, 'P'
						);
					}

					auto empty_node = pn_node->AddChild<r2bix_node::Node>();

					auto btn_node = empty_node->AddChild<r2bix_node::UIButtonNode>();
					btn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 7, 3 );
					btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetSize( 11, 5 );
					{
						auto rect_node = btn_node->AddChild<r2bix_node::RectNode>();
						rect_node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
						rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
							btn_node->GetComponent<r2bix_component::UIButtonComponent>()->GetWidth()
							, btn_node->GetComponent<r2bix_component::UIButtonComponent>()->GetHeight()
						);

						btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetCallback4CursorResponse( [rect_node]( r2bix_ui::eCursorStatus s )->bool
						{
							switch( s )
							{
							case r2bix_ui::eCursorStatus::CursorOver:
								rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Red );
								break;
							case r2bix_ui::eCursorStatus::CursorMove:
								rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_Green );
								break;
							case r2bix_ui::eCursorStatus::CursorLeave:
								rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_White );
								break;
							}

							return false;
						} );

						btn_node->GetComponent<r2bix_component::UIButtonComponent>()->SetCallback4KeyResponse( [rect_node]( int, r2bix_ui::eKeyStatus s )->bool
						{
							switch( s )
							{
							case r2bix_ui::eKeyStatus::Push:
								rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightAqua );
								break;
							case r2bix_ui::eKeyStatus::Pressed:
								rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightYellow );
								break;
							case r2bix_ui::eKeyStatus::Release:
								rect_node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->FillColorAll( r2bix::eBackgroundColor::BG_LightPurple );
								break;
							}

							return false;
						} );
					}
				}
			}

			//
			// Process
			//
			director.Run();

			//
			// Terminate
			//
			director.Terminate();

			return r2tm::eDoLeaveAction::Pause;
		};
	}






	r2tm::TitleFunctionT Pivot::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Pivot";
		};
	}
	r2tm::DoFunctionT Pivot::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 13, 5 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( auto node = r2bix_node::PivotNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TransformComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TextureRenderComponent>() );

			LS();

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}






	r2tm::TitleFunctionT Rect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Rect";
		};
	}
	r2tm::DoFunctionT Rect::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_SUB( r2bix_render::Camera camera( 0, 0, 13, 5 ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			LS();

			DECLARATION_MAIN( auto node = r2bix_node::RectNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TransformComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::CustomTextureComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::TextureRenderComponent>() );
			EXPECT_NE( nullptr, node->GetComponent<r2bix_component::RectComponent>() );

			LS();

			{
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::RectComponent>()->Set( 3, 3 ) );

				LF();

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			{
				PROCESS_MAIN( node->GetComponent<r2bix_component::RectComponent>()->Set( 5, 4, 'x' ));

				LF();

				render_target.FillCharacterAll( '=' );
				node->Render( &camera, &render_target, r2::PointInt::GetZERO() );
				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}