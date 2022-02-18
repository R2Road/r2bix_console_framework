#include "pch.h"
#include "renderable_test.h"

#include <Windows.h>

#include "base/r2base_eTestEndAction.h"

#include "render/r2render_Camera.h"
#include "render/r2render_iRenderable.h"
#include "render/r2render_VisibleResource.h"

namespace renderable_test
{
	class RenderableObject : r2render::iRenderable
	{
	public:
		RenderableObject( const r2::PointInt& position, const r2::SizeInt& size ) :
			mPosition( position )
			, mVR( size.GetWidth(), size.GetHeight(), 'R' )
		{}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override
		{
			std::cout << "world space : my pos : " << mPosition.GetX() << "   " << mPosition.GetY() << r2::linefeed;
			std::cout << "world space : camera pos : " << camera->GetPoint().GetX() << "   " << camera->GetPoint().GetY() << r2::linefeed2;

			//
			// World Space : My Rect
			//
			{
				const r2::RectInt my_world_space_rect( mVR.GetVisibleRect().GetOrigin() + mPosition, mVR.GetVisibleRect().GetSize() );
				std::cout << "world space : my rect :"
					<< " " << my_world_space_rect.GetMinX() << " " << my_world_space_rect.GetMinY()
					<< " " << my_world_space_rect.GetMaxX() << " " << my_world_space_rect.GetMaxY()
					<< r2::linefeed2;

				if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
				{
					return;
				}
				else
				{
					std::cout << "===== My Rect Is Valid =====" << r2::linefeed2;
				}
			}

			//
			// Camera Space : My Position
			//
			const auto camera_space_my_position = mPosition - camera->GetPoint();
			std::cout << "camera space : my pos : " << camera_space_my_position.GetX() << "   " << camera_space_my_position.GetY() << r2::linefeed2;

			//
			// Render Target Space : My Position
			//
			const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();
			std::cout << "render target space : my pos : " << render_target_space_my_position.GetX() << "   " << render_target_space_my_position.GetY() << r2::linefeed2;

			//
			//
			//
			render_target->Fill( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), 'A' );
		}

		r2::PointInt mPosition;
		r2render::VisibleResource mVR;
	};

	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Basic";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return[]()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;
			
			r2render::Camera camera( { 20, 25 }, { 20, 10 } );
			r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			RenderableObject renderable_object( { 16, 22 }, { 10, 10 } );

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2::linefeed;
				std::cout << r2::tab2 << "r2render::VisibleResource render_target( camera.GetWidth(), camera.GetHeight(), ' ' );" << r2::linefeed2;
				std::cout << r2::tab2 << "RenderableObject renderable_object( { 19, 22 }, { 10, 10 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show : Renderable Object Rect( +, O ), Camera Rect( #, X )" << r2::linefeed2;

				{
					for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() > y; ++y )
					{
						for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() > x; ++x )
						{
							SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '#';
						}
					}
				}

				{
					auto current_rect = renderable_object.mVR.GetVisibleRect();
					current_rect.SetOrigin( current_rect.GetOrigin() + renderable_object.mPosition );

					for( int y = current_rect.GetMinY(); current_rect.GetMaxY() > y; ++y )
					{
						for( int x = current_rect.GetMinX(); current_rect.GetMaxX() > x; ++x )
						{
							SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '+';
						}
					}
				}

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { static_cast<short>( renderable_object.mPosition.GetX() ), static_cast<short>( renderable_object.mPosition.GetY() ) } );
				std::cout << 'O';

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );
			}

			std::cout << r2::split;

			DWORD ret;
			system( "pause" );
			FillConsoleOutputCharacterA( GetStdHandle( STD_OUTPUT_HANDLE ), ' ', 40 * 120, { 0, 13 }, &ret );

			{
				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 13 } );

				std::cout << r2::tab << "+ Show Render Target" << r2::linefeed2;

				renderable_object.Render( &camera, &render_target );

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

				SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { 0, 50 } );
			}

			return r2base::eTestEndAction::Pause;
		};
	}
}