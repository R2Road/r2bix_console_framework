#include "window_input_test.h"

#include <algorithm>

#include "r2bix/r2bix_input_KeyboardInputCollector.h"
#include "r2bix/r2bix_input_KeyboardInputListener.h"

#include "r2/r2_RectInt.h"
#include "r2/r2_FPSTimer.h"
#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_WindowUtility.h"

namespace window_input_test
{
	r2cm::iItem::TitleFunctionT KeyStatus::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Window Input : KeyStatus";
		};
	}
	r2cm::iItem::DoFunctionT KeyStatus::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			std::cout << "[ESC] Exit" << r2cm::linefeed;
			std::cout << "[A] ..." << r2cm::linefeed;

			r2bix_input::KeyboardInputCollector keyboard_input_collector;
			r2bix_input::KeyboardInputListener keyboard_input_listener( {
				0x1B		// esc
				, 0x41		// a
			} );

			keyboard_input_collector.AddListener( &keyboard_input_listener );

			std::cout << r2cm::split;

			{
				auto last_input_status = keyboard_input_listener.Get( 1 );
				while( 1 )
				{
					keyboard_input_collector.Collect();
					keyboard_input_listener.Update();

					//
					// ESC
					//
					if( keyboard_input_listener.IsPushed( 0 ) )
					{
						break;
					}

					//
					// A
					//
					if( last_input_status != keyboard_input_listener.Get( 1 ) )
					{
						last_input_status = keyboard_input_listener.Get( 1 );
						std::cout << "status : " << static_cast<int>( last_input_status ) << r2cm::linefeed;
					}
				}
			}

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TestKeyboardInputCollector::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Keyboard Input Collector";
		};
	}
	r2cm::iItem::DoFunctionT TestKeyboardInputCollector::GetDoFunction()
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			std::cout << "[ESC] Exit" << r2cm::linefeed;
			std::cout << "[WASD] Move" << r2cm::linefeed;

			r2bix_input::KeyboardInputCollector keyboard_input_collector;
			r2bix_input::KeyboardInputListener keyboard_input_listener( {
				0x1B		// esc
				, 0x41		// a
				, 0x44		// d
				, 0x53		// s
				, 0x57		// w
			} );

			keyboard_input_collector.AddListener( &keyboard_input_listener );

			std::cout << r2cm::split;

			{
				r2::FPSTimer fps_timer( 60u );
				r2::RectInt stage_area( 6, 10, 50, 30 );
				r2cm::WindowUtility::CursorPoint pos{ 20, 20 };
				r2cm::WindowUtility::CursorPoint temp_pos{ 20, 20 };

				r2cm::WindowUtility::MoveCursorPoint( pos );
				std::cout << '@';

				while( 1 )
				{
					keyboard_input_collector.Collect();
					keyboard_input_listener.Update();

					//
					// ESC
					//
					if( keyboard_input_listener.IsPushed( 0 ) )
					{
						break;
					}

					if( fps_timer.Update() )
					{
						temp_pos = pos;

						if( keyboard_input_listener.HasInput( 1 ) )
						{
							--temp_pos.x;
						}
						if( keyboard_input_listener.HasInput( 2 ) )
						{
							++temp_pos.x;
						}
						if( keyboard_input_listener.HasInput( 4 ) )
						{
							--temp_pos.y;
						}
						if( keyboard_input_listener.HasInput( 3 ) )
						{
							++temp_pos.y;
						}
						if( !stage_area.ContainsPoint( temp_pos.x, temp_pos.y ) )
						{
							temp_pos.x = std::clamp( temp_pos.x, static_cast<short>( stage_area.GetMinX() ), static_cast<short>( stage_area.GetMaxX() ) );
							temp_pos.y = std::clamp( temp_pos.y, static_cast<short>( stage_area.GetMinY() ), static_cast<short>( stage_area.GetMaxY() ) );
						}

						if( temp_pos.x != pos.x || temp_pos.y != pos.y )
						{
							r2cm::WindowUtility::MoveCursorPoint( pos );
							std::cout << ' ';
							r2cm::WindowUtility::MoveCursorPoint( temp_pos );
							std::cout << '@';

							pos = temp_pos;
						}
					}
				}
			}

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}