#include "pch.h"
#include "animation_test.h"

#include <conio.h>
#include <Windows.h>

#include "r2cm/r2cm_eTestEndAction.h"

#include "base/r2base_FPSTimer.h"
#include "render/r2render_iRenderable.h"
#include "render/r2render_Texture.h"

namespace animation_test
{
	class Renderable4AnimationTest : public r2render::iRenderable
	{
	public:
		Renderable4AnimationTest( const int x, const int y, const uint32_t width, const char* chars ) :
			mVisibleResource( width, chars )
			, mRect( { x, y, mVisibleResource.GetWidth(), mVisibleResource.GetHeight() } )
		{}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const /*render_target*/ ) override
		{
			if( !camera->GetRect().IntersectsRect( mRect ) )
			{
				return;
			}

			const auto visible_rect = camera->GetRect().IntersectsWithRect( mRect );

			const COORD pivot_pos = {
				static_cast<short>( visible_rect.GetMinX() - camera->GetX() )
				, static_cast<short>( visible_rect.GetMinY() - camera->GetY() )
			};

			const int resource_offset_y = visible_rect.GetMinY() - mRect.GetMinY();
			const int resource_offset_x = visible_rect.GetMinX() - mRect.GetMinX();

			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			for( int y = 0; y < visible_rect.GetHeight(); ++y )
			{
				for( int x = 0; x < visible_rect.GetWidth(); ++x )
				{
					SetConsoleCursorPosition( stdHandle, {
						pivot_pos.X + static_cast<short>( x )
						, pivot_pos.Y + static_cast<short>( y ) }
					);

					std::cout << mVisibleResource.Get(
						resource_offset_x + x
						, resource_offset_y + y
					);
				}
			}
		}

	private:
		r2render::Texture mVisibleResource;
		r2::RectInt mRect;
	};

	Basic::Basic() : mCamera( { 0, 0 }, { 60, 30 } ), mRenderer()
	{}
	r2cm::iItem::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Animation - Basic";
		};
	}
	r2cm::iItem::DoFunc Basic::GetDoFunction()
	{
		GetInstance().mRenderer.Clear();
		GetInstance().mRenderer.SetCamera( &mCamera );

		{
			static Renderable4AnimationTest tr( 8, 5, 6u, "######" "#    #" "#    #" "#    #" "#    #" "######" );
			GetInstance().mRenderer.Add( &tr );
		}

		{
			static Renderable4AnimationTest tr( 8, 5, 6u, " #### " " #  # " " #  # " " #  # " " #  # " " #### " );
			GetInstance().mRenderer.Add( &tr );
		}

		{
			static Renderable4AnimationTest tr( 8, 5, 6u, "  ##  " "  ##  " "  ##  " "  ##  " "  ##  " "  ##  " );
			GetInstance().mRenderer.Add( &tr );
		}

		return [&rd = GetInstance().mRenderer, &cam = mCamera]()->r2cm::eTestEndAction
		{
			r2base::FPSTimer frame_manager( 30u );
			frame_manager.Reset();

			int x = 0;
			int y = 0;
			bool process = true;
			while( process )
			{
				if( frame_manager.Update() )
				{
					rd.Draw();
				}

				if( _kbhit() )
				{
					switch( _getch() )
					{
					case 'w': // up
						y -= 1;
						break;
					case 's': // down
						y += 1;
						break;
					case 'a': // left
						x -= 1;
						break;
					case 'd': // right
						x += 1;
						break;

					case 27: // ESC
						process = false;
						break;
					}
				}

				cam.SetPoint( x, y );
			}

			return r2cm::eTestEndAction::Pause;
		};
	}
}