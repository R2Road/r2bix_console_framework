#include "pch.h"
#include "component_test.h"

#include <Windows.h>

#include "r2/r2_Inspector.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "base/r2base_Director.h"
#include "base/r2base_Node.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureFrameAnimationComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"
#include "render/r2render_TextureFrame.h"

#include "p2048/p2048table_TextureTable.h"

namespace component_test
{
	r2cm::iItem::TitleFuncT ComponentID::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Component ID";
		};
	}
	r2cm::iItem::DoFuncT ComponentID::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2base::Director dummy_director;
			auto node = r2base::Node::Create( dummy_director );
			auto transform_1 = r2component::TransformComponent::Create( *node );
			auto transform_2 = r2component::TransformComponent::Create( *node );
			auto texture_render_1 = r2component::TextureRenderComponent::Create( *node );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "auto transform_1 = r2component::TransformComponent::Create( *node );" << r2::linefeed;
				std::cout << r2::tab << "auto transform_2 = r2component::TransformComponent::Create( *node );" << r2::linefeed;
				std::cout << r2::tab << "auto texture_render_1 = r2component::TextureRenderComponent::Create( *node );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << "transform_1->GetStaticID();" << " > " << transform_1->GetStaticID() << r2::linefeed;
				EXPECT_EQ( transform_1->GetStaticID(), r2base::ComponentStaticID<r2component::TransformComponent>::Get() );
				EXPECT_EQ( transform_1->GetStaticID(), transform_2->GetStaticID() );

				std::cout << r2::linefeed2;

				std::cout << "texture_render_1->GetStaticID();" << " > " << texture_render_1->GetStaticID() << r2::linefeed;
				EXPECT_EQ( texture_render_1->GetStaticID(), r2base::ComponentStaticID<r2component::TextureRenderComponent>::Get() );
				EXPECT_NE( texture_render_1->GetStaticID(), transform_1->GetStaticID() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT GetComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "GetComponent";
		};
	}
	r2cm::iItem::DoFuncT GetComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2base::Director dummy_director;
			auto node = r2base::Node::Create( dummy_director );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed;
				std::cout << r2::tab << "auto node = r2base::Node::Create( dummy_director );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_NE( nullptr, node->GetComponent<r2component::TransformComponent>() );
				EXPECT_EQ( node->mTransformComponent, node->GetComponent<r2component::TransformComponent>() );

				EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT AddComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "AddComponent";
		};
	}
	r2cm::iItem::DoFuncT AddComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			r2base::Director dummy_director;
			auto node = r2base::Node::Create( dummy_director );

			std::cout << r2::split;

			{
				std::cout << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab << "r2base::Director dummy_director;" << r2::linefeed;
				std::cout << r2::tab << "auto node = r2base::Node::Create( dummy_director );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				EXPECT_EQ( nullptr, node->GetComponent<r2component::TextureRenderComponent>() );

				EXPECT_TRUE( node->AddComponent<r2component::TextureRenderComponent>() );
				EXPECT_FALSE( node->AddComponent<r2component::TextureRenderComponent>() );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureRenderComponentTest_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 1";
		};
	}
	r2cm::iItem::DoFuncT TextureRenderComponentTest_1::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2::linefeed;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );

			std::cout << r2::split;

			EXPECT_TRUE( node->AddComponent<r2component::TextureRenderComponent>() );

			std::cout << r2::linefeed;

			DECLARATION_MAIN( auto component = node->GetComponent<r2component::TextureRenderComponent>() );
			PROCESS_MAIN( component->SetRect( -1, -1, 2, 2 ) );

			std::cout << r2::split;

			EXPECT_EQ( nullptr, component->GetTexture() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 32 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureRenderComponentTest_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Render Component 2";
		};
	}
	r2cm::iItem::DoFuncT TextureRenderComponentTest_2::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2::linefeed;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2::split;

			EXPECT_TRUE( node->AddComponent<r2component::TextureRenderComponent>() );

			std::cout << r2::linefeed;

			DECLARATION_MAIN( auto component = node->GetComponent<r2component::TextureRenderComponent>() );
			PROCESS_MAIN( component->SetRect( -1, -1, 2, 2 ) );

			std::cout << r2::split;

			DECLARATION_MAIN( r2render::Texture texture( 3, 3, 'A' ) );
			PROCESS_MAIN( component->SetTexture( &texture ) );
			EXPECT_NE( nullptr, component->GetTexture() );
			EXPECT_EQ( &texture, component->GetTexture() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 32 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT LabelComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Label Component";
		};
	}
	r2cm::iItem::DoFuncT LabelComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2::linefeed;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2::split;

			EXPECT_TRUE( node->AddComponent<r2component::LabelComponent>() );
			EXPECT_TRUE( node->AddComponent<r2component::TextureRenderComponent>() );

			std::cout << r2::linefeed;

			DECLARATION_MAIN( auto component = node->GetComponent<r2component::TextureRenderComponent>() );
			PROCESS_MAIN( component->SetTexture( node->GetComponent<r2component::LabelComponent>()->GetTexture() ) );
			PROCESS_MAIN( component->SetRect( -1, -1, 5, 0 ) );

			std::cout << r2::linefeed;

			DECLARATION_MAIN( const char* const dummy_text = "Bla Bla Bla" );
			PROCESS_MAIN( node->GetComponent<r2component::LabelComponent>()->SetString( dummy_text ) );
			EXPECT_EQ( dummy_text, node->GetComponent<r2component::LabelComponent>()->GetString() );

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 34 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureFrameRenderComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameRender Component";
		};
	}
	r2cm::iItem::DoFuncT TextureFrameRenderComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2::linefeed;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2::split;

			{
				EXPECT_FALSE( node->GetComponent<r2component::TextureFrameRenderComponent>() );
				PROCESS_MAIN( node->AddComponent<r2component::TextureFrameRenderComponent>() );
				EXPECT_TRUE( node->GetComponent<r2component::TextureFrameRenderComponent>() );
			}

			std::cout << r2::linefeed;

			DECLARATION_MAIN( r2render::Texture texture( 3, 3,
				"123"
				"456"
				"abc"
			) );
			DECLARATION_MAIN( r2render::TextureFrame frame( &texture ) );
			PROCESS_MAIN( frame.SetVisibleRect( r2::RectInt( frame.GetMinX() + 1, frame.GetMinY() + 1, frame.GetWidth(), frame.GetHeight() ) ) );

			std::cout << r2::linefeed;

			{
				EXPECT_FALSE( node->GetComponent<r2component::TextureFrameRenderComponent>()->GetTextureFrame() );
				PROCESS_MAIN( node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( &frame ) );
				EXPECT_TRUE( node->GetComponent<r2component::TextureFrameRenderComponent>()->GetTextureFrame() );
				EXPECT_EQ( &frame, node->GetComponent<r2component::TextureFrameRenderComponent>()->GetTextureFrame() );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 34 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}



	r2cm::iItem::TitleFuncT TextureFrameAnimationComponentTest::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrameAnimation Component";
		};
	}
	r2cm::iItem::DoFuncT TextureFrameAnimationComponentTest::GetDoFunction()
	{
		return[]()->r2cm::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			p2048table::TextureTable::GetInstance().Load();

			std::cout << r2::split;

			DECLARATION_SUB( r2render::Camera camera( { 20, 25 }, { 14, 6 } ) );
			DECLARATION_SUB( r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' ) );

			std::cout << r2::linefeed;

			DECLARATION_SUB( r2base::Director dummy_director );

			std::cout << r2::linefeed;

			DECLARATION_SUB( auto node = r2base::Node::Create( dummy_director ) );
			PROCESS_SUB( node->mTransformComponent->SetPosition( 20, 25 ) );

			std::cout << r2::split;

			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameRenderComponent>() );
			EXPECT_TRUE( node->GetComponent<r2component::TextureFrameRenderComponent>() );

			EXPECT_TRUE( node->AddComponent<r2component::TextureFrameAnimationComponent>() );

			std::cout << r2::split;

			{
				DECLARATION_MAIN( auto tfac = node->GetComponent<r2component::TextureFrameAnimationComponent>() );
				PROCESS_MAIN( tfac->AddTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "dguy_walk_1" ) ) );
				PROCESS_MAIN( tfac->AddTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "dguy_walk_2" ) ) );
				PROCESS_MAIN( tfac->AddTextureFrame( p2048table::TextureTable::GetInstance().GetTextureFrame( "dguy_walk_3" ) ) );
			}

			std::cout << r2::split;

			{
				PROCESS_MAIN( node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );
			}

			std::cout << r2::split;

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 34 } );

				std::cout << "+ Show Render Target" << r2::linefeed2;

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2::linefeed;
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 45 } );
			}

			std::cout << r2::split;

			return r2cm::eTestEndAction::Pause;
		};
	}
}