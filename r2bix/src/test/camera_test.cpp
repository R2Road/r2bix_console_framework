#include "pch.h"
#include "camera_test.h"

#include <conio.h>
#include <Windows.h>

#include "base/r2base_eTestEndAction.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_RectInt.h"
#include "render/r2_iRenderable.h"
#include "render/r2_VisibleResource.h"

namespace camera_test
{
	r2base::iTest::TitleFunc CameraRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Rect";
		};
	}
	r2base::iTest::DoFunc CameraRect::GetDoFunction()
	{
		return[]()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			r2::Camera camera;
			camera.SetPoint( { 14, 14 } );

			{
				std::cout << r2::tab << "+ Declaration" << r2::linefeed2;
				std::cout << r2::tab2 << "r2::Camera camera;" << r2::linefeed;
				std::cout << r2::tab2 << "camera.SetPoint( { 14, 14 } );" << r2::linefeed;
			}

			std::cout << r2::split;

			{
				std::cout << r2::tab << "+ Show Camera Rect" << r2::linefeed2;

				HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );

				for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() > y; ++y )
				{
					for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() > x; ++x )
					{
						SetConsoleCursorPosition( stdHandle, { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '#';
					}
				}
				std::cout << r2::linefeed;
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}


namespace camera_test
{
	class TempRenderable : public r2::iRenderable
	{
	public:
		TempRenderable( const int x, const int y, const uint32_t width, const char* chars ) :
			mPoint( { x, y } )
			, mVisibleResource( width, chars )
		{}

		void Render( const r2::Camera* const camera ) override
		{
			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			COORD pos = {
				static_cast<short>( mPoint.GetX() - camera->GetPoint().GetX() )
				, static_cast<short>( mPoint.GetY() - camera->GetPoint().GetY() )
			};
			SetConsoleCursorPosition( stdHandle, pos );

			int count = 0;
			for( const char element : mVisibleResource )
			{
				std::cout << element;

				++count;
				if( mVisibleResource.GetWidth() <= count )
				{
					count = 0;
					pos.Y += 1;
					SetConsoleCursorPosition( stdHandle, pos );
				}
			}
		}

	private:
		r2::PointInt mPoint;
		r2::VisibleResource mVisibleResource;
	};

	r2base::iTest::TitleFunc CameraMove1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move 1";
		};
	}
	r2base::iTest::DoFunc CameraMove1::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			r2::Camera camera;
			r2::Renderer renderer;

			renderer.Clear();
			renderer.SetCamera( &camera );

			{
				std::string str( "# " );
				str += GetInstance().GetTitleFunction()( );
				str += " #";
				static TempRenderable tr( 0, 0, static_cast<uint32_t>( str.length() ), str.c_str() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[ESC] Return to Root" );
				static TempRenderable tr( 0, 1, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[W,A,S,D] Move Camera" );
				static TempRenderable tr( 0, 2, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				static TempRenderable tr( 2, 4, 3u, "###" "# #" "###" );
				renderer.Add( &tr );
			}

			{
				static TempRenderable tr( 11, 7, 7u, "#######" "#     #" "#     #" "#     #" "#     #" "#######" );
				renderer.Add( &tr );
			}

			int x = 0;
			int y = 0;
			bool process = true;
			do
			{
				renderer.Draw();

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

				camera.SetPoint( x, y );
			} while( process );

			return r2base::eTestEndAction::None;
		};
	}
}


namespace camera_test
{
	class Renderable4CameraTest : public r2::iRenderable
	{
	public:
		Renderable4CameraTest( const int x, const int y, const uint32_t width, const char* chars ) :
			mVisibleResource( width, chars )
			, mRect( { x, y, mVisibleResource.GetWidth(), mVisibleResource.GetHeight() } )
		{}

		void Render( const r2::Camera* const camera ) override
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
		r2::VisibleResource mVisibleResource;
		r2::RectInt mRect;
	};

	r2base::iTest::TitleFunc CameraMove2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move 2";
		};
	}
	r2base::iTest::DoFunc CameraMove2::GetDoFunction()
	{
		return[]()->r2base::eTestEndAction
		{
			r2::Camera camera;

			r2::Renderer renderer;
			renderer.Clear();
			renderer.SetCamera( &camera );

			{
				std::string str( "# " );
				str += GetInstance().GetTitleFunction()( );
				str += " #";
				static Renderable4CameraTest tr( 0, 0, static_cast<uint32_t>( str.length() ), str.c_str() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[ESC] Return to Root" );
				static Renderable4CameraTest tr( 0, 1, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				std::string_view str( "[W,A,S,D] Move Camera" );
				static Renderable4CameraTest tr( 0, 2, static_cast<uint32_t>( str.length() ), str.data() );
				renderer.Add( &tr );
			}

			{
				static Renderable4CameraTest tr( 2, 4, 3u, "###" "# #" "###" );
				renderer.Add( &tr );
			}

			{
				static Renderable4CameraTest tr( 11, 7, 7u, "#######" "#     #" "#     #" "#     #" "#     #" "#######" );
				renderer.Add( &tr );
			}

			int x = 0;
			int y = 0;
			bool process = true;
			do
			{
				renderer.Draw();

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

				camera.SetPoint( x, y );
			} while( process );

			return r2base::eTestEndAction::None;
		};
	}
}