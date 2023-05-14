#include "test_p2048_stageviewnode.h"

#include "r2bix/r2bix_Director.h"
#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"
#include "r2bix/r2bix_render_Camera.h"

#include "p2048/p2048_Stage.h"
#include "p2048/p2048_StageViewComponent.h"
#include "p2048/p2048_StageViewNode.h"
#include "p2048/p2048table_TextureTable.h"

#include "test/Utility4Test.h"
#include "r2cm/r2cm_WindowUtility.h"

namespace test_p2048_stageviewnode
{
	r2cm::iItem::TitleFunctionT Generate::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "StageViewNode : Generate";
		};
	}
	r2cm::iItem::DoFunctionT Generate::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 41, 21 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '-' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( auto stage_view_node = p2048::StageViewNode::Create( dummy_director ) );
			EXPECT_NE( nullptr, stage_view_node->GetComponent<p2048::StageViewComponent>() );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( stage_view_node->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT Setup_Render::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "StageViewNode : Setup And Render";
		};
	}
	r2cm::iItem::DoFunctionT Setup_Render::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			p2048table::TextureTable::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 41, 21 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '-' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( p2048::Stage stage( 4, 4 ) );
			PROCESS_MAIN( stage.Add( 0, 0, 32 ) );
			PROCESS_MAIN( stage.Add( 0, 1, 64 ) );
			PROCESS_MAIN( stage.Add( 3, 0, 512 ) );
			PROCESS_MAIN( stage.Add( 0, 3, 1024 ) );
			PROCESS_MAIN( stage.Add( 3, 3, 2048 ) );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( auto svn = p2048::StageViewNode::Create( dummy_director ) );
			DECLARATION_MAIN( auto svc = svn->GetComponent<p2048::StageViewComponent>() );
			PROCESS_MAIN( svc->Setup( stage ) );
			PROCESS_MAIN( svn->GetComponent<r2bix_component::TransformComponent>()->SetPosition( -svc->GetWidth() * 0.5f, -svc->GetHeight() * 0.5f ) );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( svn->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT UpdateView::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "StageViewNode : UpdateView";
		};
	}
	r2cm::iItem::DoFunctionT UpdateView::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			p2048table::TextureTable::GetInstance().Load();

			std::cout << r2cm::split;

			DECLARATION_SUB( r2bix_render::Camera camera( { 0, 0 }, { 41, 21 } ) );
			DECLARATION_SUB( r2bix_render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '-' ) );
			DECLARATION_SUB( r2bix::Director dummy_director( {} ) );

			std::cout << r2cm::split;

			DECLARATION_MAIN( p2048::Stage stage( 4, 4 ) );
			PROCESS_MAIN( stage.Add( 0, 0, 32 ) );
			PROCESS_MAIN( stage.Add( 0, 1, 64 ) );
			PROCESS_MAIN( stage.Add( 3, 0, 512 ) );
			PROCESS_MAIN( stage.Add( 0, 3, 1024 ) );
			PROCESS_MAIN( stage.Add( 3, 3, 2048 ) );

			std::cout << r2cm::linefeed;

			DECLARATION_MAIN( auto svn = p2048::StageViewNode::Create( dummy_director ) );
			DECLARATION_MAIN( auto svc = svn->GetComponent<p2048::StageViewComponent>() );
			PROCESS_MAIN( svc->Setup( stage ) );
			PROCESS_MAIN( svc->UpdateView() );
			PROCESS_MAIN( svn->GetComponent<r2bix_component::TransformComponent>()->SetPosition( -svc->GetWidth() * 0.5f, -svc->GetHeight() * 0.5f ) );

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( svn->Render( &camera, &render_target, r2::PointInt::GetZERO() ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTexture( render_target );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}