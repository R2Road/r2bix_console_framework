#include "camera_test.h"

#include <conio.h>

#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"

#include "r2/r2_PointInt.h"
#include "r2/r2_RectInt.h"
#include "r2bix/r2bix_render_Camera.h"
#include "r2bix/r2bix_render_Texture.h"


namespace camera_test
{
	std::ostream& operator<<( std::ostream& o, const r2::PointInt& p )
	{
		o << "x : " << p.GetX() << "      " "y : " << p.GetY() << r2tm::linefeed;
		return o;
	}
	std::ostream& operator<<( std::ostream& o, const r2::Size<int>& s )
	{
		o << "s : " << s.GetWidth() << "      " "h : " << s.GetHeight() << r2tm::linefeed;
		return o;
	}

	r2tm::TitleFunctionT Declaration::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera : Declaration";
		};
	}
	r2tm::DoFunctionT Declaration::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( const r2::Point<int> position( 20, 30 ) );
			DECLARATION_MAIN( const r2::Size<int> size( 10, 50 ) );
			DECLARATION_MAIN( r2bix_render::Camera camera( position, size ) );

			LS();

			{
				EXPECT_EQ( position.GetX(), camera.GetX() );
				EXPECT_EQ( position.GetY(), camera.GetY() );
				EXPECT_EQ( position, camera.GetPoint() );
				EXPECT_EQ( size.GetWidth(), camera.GetWidth() );
				EXPECT_EQ( size.GetHeight(), camera.GetHeight() );

				LF();

				EXPECT_EQ( ( size + r2::Size<int>( -1, -1 ) ), camera.GetCameraSpaceRect().GetSize() );
				EXPECT_EQ( -( ( size.GetWidth() - 1 ) / 2 ), camera.GetCameraSpaceRect().GetOrigin().GetX() );
				EXPECT_EQ( -( ( size.GetHeight() - 1 ) / 2 ), camera.GetCameraSpaceRect().GetOrigin().GetY() );

				LF();

				EXPECT_EQ( ( size + r2::Size<int>( -1, -1 ) ), camera.GetRect().GetSize() );
				EXPECT_EQ( position.GetX() - ( ( size.GetWidth() - 1 ) / 2 ), camera.GetRect().GetOrigin().GetX() );
				EXPECT_EQ( position.GetY() - ( ( size.GetHeight() - 1 ) / 2 ), camera.GetRect().GetOrigin().GetY() );
			}

			LS();

			{
				OUTPUT_VALUE( camera.GetX() );
				OUTPUT_VALUE( camera.GetY() );
				OUTPUT_VALUE( camera.GetWidth() );
				OUTPUT_VALUE( camera.GetHeight() );

				LF();

				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetOrigin().GetX() );
				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetOrigin().GetY() );
				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetSize().GetWidth() );
				OUTPUT_VALUE( camera.GetCameraSpaceRect().GetSize().GetHeight() );

				LF();

				OUTPUT_VALUE( camera.GetRect().GetOrigin().GetX() );
				OUTPUT_VALUE( camera.GetRect().GetOrigin().GetY() );
				OUTPUT_VALUE( camera.GetRect().GetSize().GetWidth() );
				OUTPUT_VALUE( camera.GetRect().GetSize().GetHeight() );
			}

			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CameraPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Position";
		};
	}
	r2tm::DoFunctionT CameraPosition::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_render::Camera camera( 20, 30, 20, 10 ) );

			LS();

			{
				std::cout << r2tm::tab << "+ Show Camera Position" << r2tm::linefeed2;

				std::cout << r2tm::linefeed3 << r2tm::linefeed3 << r2tm::linefeed3 << r2tm::linefeed3 << r2tm::linefeed3;

				r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
				r2tm::WindowUtility::MoveCursorPoint( { 0, 50 } );
			}


			LS();

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CameraRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Rect";
		};
	}
	r2tm::DoFunctionT CameraRect::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			r2bix_render::Camera camera( 20, 30, 20, 10 );

			{
				std::cout << r2tm::tab << "+ Declaration" << r2tm::linefeed2;
				std::cout << r2tm::tab2 << "r2bix_render::Camera camera( { 20, 30 }, { 20, 10 } );" << r2tm::linefeed;
			}

			LS();

			{
				std::cout << r2tm::tab << "+ Show Camera Rect" << r2tm::linefeed2;

				for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
				{
					for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
					{
						r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( x ), static_cast<short>( y ) } );
						std::cout << '#';
					}
				}
				
				r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
				std::cout << 'X';
			}

			r2tm::WindowUtility::MoveCursorPoint( { 0, 50 } );

			return r2tm::eDoLeaveAction::Pause;
		};
	}



	r2tm::TitleFunctionT CameraMove::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Camera Move";
		};
	}
	r2tm::DoFunctionT CameraMove::GetDoFunction() const
	{
		return[]()->r2tm::eDoLeaveAction
		{
			LS();

			DECLARATION_MAIN( r2bix_render::Camera camera( 20, 30, 19, 9 ) );

			LS();

			std::cout << r2tm::tab << "+ Show Camera Rect" << r2tm::linefeed2;
			std::cout << "[ESC] Exit" << r2tm::linefeed;
			std::cout << "[Any Key] Move Camera" << r2tm::linefeed;

			LS();

			const auto current_cursor_point = r2tm::WindowUtility::GetCursorPoint();
			int step = 0;
			int input = 0;
			do
			{
				r2tm::WindowUtility::MoveCursorPointWithClearBuffer( current_cursor_point );

				if( 0 == step )
				{
					camera.SetPoint( 30, 20 );
					step = 1;
				}
				else
				{
					camera.SetPoint( 20, 30 );
					step = 0;
				}

				{
					for( int y = camera.GetRect().GetMinY(); camera.GetRect().GetMaxY() >= y; ++y )
					{
						for( int x = camera.GetRect().GetMinX(); camera.GetRect().GetMaxX() >= x; ++x )
						{
							r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( x ), static_cast<short>( y ) } );
							std::cout << '#';
						}
					}

					r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( camera.GetX() ), static_cast<short>( camera.GetY() ) } );
					std::cout << 'X';
				}

				r2tm::WindowUtility::MoveCursorPoint( { 0, 40 } );
				input = _getch();

			} while( 27 != input );

			return r2tm::eDoLeaveAction::None;
		};
	}
}