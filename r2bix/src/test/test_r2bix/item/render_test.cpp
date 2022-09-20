#include "render_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"

#include "r2bix/r2base_Director.h"
#include "r2bix/r2base_Node.h"
#include "r2bix/r2render_Camera.h"
#include "r2bix/r2render_Texture.h"

namespace render_test
{
	class RenderTestNode : r2base::Node
	{
	public:
		RenderTestNode( r2base::Director& director, const r2::PointInt& position, const r2::SizeInt size, const r2::PointInt rect_offset ) : r2base::Node( director )
			, mPosition( position )
			, mTexture( size.GetWidth(), size.GetHeight() )
			, mRect( rect_offset.GetX(), rect_offset.GetY(), mTexture.GetWidth() - 1, mTexture.GetHeight() - 1 )
		{
			for( int y = 0; mTexture.GetHeight() > y; ++y )
			{
				for( int x = 0; mTexture.GetWidth() > x; ++x )
				{
					mTexture.FillCharacter( x, y, static_cast<char>( 48 + x ) );
				}
			}
		}

		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target, r2::PointInt /*offset*/ ) override
		{
			std::cout << "world space : my pos : " << mPosition.GetX() << "   " << mPosition.GetY() << r2cm::linefeed;
			std::cout << "world space : camera pos : " << camera->GetPoint().GetX() << "   " << camera->GetPoint().GetY() << r2cm::linefeed2;

			//
			// World Space : My Rect
			//
			{
				const r2::RectInt my_world_space_rect( mRect.GetOrigin() + mPosition, mRect.GetSize() );
				std::cout << "world space : my rect :"
					<< " " << my_world_space_rect.GetMinX() << " " << my_world_space_rect.GetMinY()
					<< " " << my_world_space_rect.GetMaxX() << " " << my_world_space_rect.GetMaxY()
					<< r2cm::linefeed2;

				if( !my_world_space_rect.IntersectsRect( camera->GetRect() ) )
				{
					return;
				}
				else
				{
					std::cout << "===== My Rect Is Valid =====" << r2cm::linefeed2;
				}
			}

			//
			// Camera Space : My Position
			//
			const auto camera_space_my_position = mPosition - camera->GetPoint();
			std::cout << "camera space : my pos : " << camera_space_my_position.GetX() << "   " << camera_space_my_position.GetY() << r2cm::linefeed2;

			//
			// Render Target Space : My Position
			//
			const auto render_target_space_my_position = camera_space_my_position - camera->GetCameraSpaceRect().GetOrigin();
			std::cout << "render target space : my pos : " << render_target_space_my_position.GetX() << "   " << render_target_space_my_position.GetY() << r2cm::linefeed2;

			//
			//
			//
			render_target->FillCharacter( render_target_space_my_position.GetX(), render_target_space_my_position.GetY(), 'A' );

			//
			// Render Target Space : My Rect
			//
			auto render_target_space_my_rect = mRect;
			std::cout << "local space : my rect :"
				<< " " << render_target_space_my_rect.GetMinX() << " " << render_target_space_my_rect.GetMinY()
				<< " " << render_target_space_my_rect.GetMaxX() << " " << render_target_space_my_rect.GetMaxY()
				<< r2cm::linefeed2;

			render_target_space_my_rect.MoveOrigin( render_target_space_my_position.GetX(), render_target_space_my_position.GetY() );
			std::cout << "render target space : my rect :"
				<< " " << render_target_space_my_rect.GetMinX() << " " << render_target_space_my_rect.GetMinY()
				<< " " << render_target_space_my_rect.GetMaxX() << " " << render_target_space_my_rect.GetMaxY()
				<< r2cm::linefeed2;

			//
			// Render Target Space : Intersect Rect
			//
			auto render_target_space_intersect_rect = render_target->GetRect().IntersectsWithRect( render_target_space_my_rect );
			std::cout << "render target space : intersect rect :"
				<< " " << render_target_space_intersect_rect.GetMinX() << " " << render_target_space_intersect_rect.GetMinY()
				<< " " << render_target_space_intersect_rect.GetMaxX() << " " << render_target_space_intersect_rect.GetMaxY()
				<< r2cm::linefeed2;

			//
			// Offset
			//
			const auto off_set_point = render_target_space_intersect_rect.GetOrigin() - render_target_space_my_rect.GetOrigin();
			std::cout << "draw offset : " << off_set_point.GetX() << "   " << off_set_point.GetY() << r2cm::linefeed2;

			{
				for( int y = render_target_space_intersect_rect.GetMinY(), ty = 0; render_target_space_intersect_rect.GetMaxY() >= y; ++y, ++ty )
				{
					for( int x = render_target_space_intersect_rect.GetMinX(), tx = 0; render_target_space_intersect_rect.GetMaxX() >= x; ++x, ++tx )
					{
						render_target->FillCharacter(
							x, y
							, mTexture.GetCharacter( off_set_point.GetX() + tx, off_set_point.GetY() + ty )
						);
					}
				}
			}
		}

		r2::PointInt mPosition;
		r2render::Texture mTexture;
		r2::RectInt mRect;
	};

	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Render Test";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction()
	{
		return[]()->r2cm::eItemLeaveAction
		{
			r2render::Camera camera( { 20, 25 }, { 20, 10 } );
			r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), '=' );

			r2base::Director dummy_director( {} );
			RenderTestNode render_test_node( dummy_director, { 12, 26 }, { 9, 9 }, { -4, -2 } );

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Declaration" << r2cm::linefeed2;
				std::cout << r2cm::tab2 << "r2render::Camera camera( { 20, 25 }, { 20, 10 } );" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "r2render::Texture render_target( camera.GetWidth(), camera.GetHeight(), ' ' );" << r2cm::linefeed2;
				std::cout << r2cm::tab2 << "r2base::Director dummy_director;" << r2cm::linefeed;
				std::cout << r2cm::tab2 << "RenderTestNode render_test_node( dummy_director, { 12, 26 }, { 9, 9 }, { -4, -2 } );" << r2cm::linefeed;
			}

			std::cout << r2cm::split;

			{
				std::cout << r2cm::tab << "+ Show : RenderTestNode, Camera Rect( #, X )" << r2cm::linefeed2;

				{
					for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
					{
						for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
						{
							r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '#';
						}
					}
				}

				{
					auto current_rect = render_test_node.mRect;
					current_rect.SetOrigin( current_rect.GetOrigin() + render_test_node.mPosition );

					for( int y = 0; current_rect.GetHeight() > y; ++y )
					{
						for( int x = 0; current_rect.GetWidth() > x; ++x )
						{
							r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( current_rect.GetMinX() + x ), static_cast<short>( current_rect.GetMinY() + y ) } );
							std::cout << render_test_node.mTexture.GetCharacter( x, y );
						}
					}
				}

				r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';

				r2cm::WindowUtility::MoveCursorPoint( { static_cast<short>( render_test_node.mPosition.GetX() ), static_cast<short>( render_test_node.mPosition.GetY() ) } );
				std::cout << '+';

				r2cm::WindowUtility::MoveCursorPoint( { 0, 50 } );
			}

			std::cout << r2cm::split;

			system( "pause" );

			{
				r2cm::WindowUtility::MoveCursorPointWithClearBuffer( { 0, 13 } );

				std::cout << r2cm::tab << "+ Show Render Target" << r2cm::linefeed2;

				render_test_node.Render( &camera, &render_target, r2::PointInt::GetZERO() );

				int current_x = 0;
				for( const auto& p : render_target )
				{
					std::cout << p;

					++current_x;

					if( render_target.GetWidth() <= current_x )
					{
						current_x = 0;
						std::cout << r2cm::linefeed;
					}
				}

				r2cm::WindowUtility::MoveCursorPoint( { 0, 50 } );
			}

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}