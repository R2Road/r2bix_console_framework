#include "console_screen_buffer_manager_test.h"

#include <conio.h>

#include "r2bix/r2bix_director_ScreenBufferManager.h"
#include "r2tm/r2tm_Inspector.h"
#include "r2tm/r2tm_ostream.h"

namespace console_screen_buffer_manager_test
{
	r2tm::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Console Screen Buffer Manager : Basic";
		};
	}
	r2tm::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2tm::eDoLeaveAction
		{
			std::cout << r2tm::split;

			DECLARATION_MAIN( r2bix_director::ScreenBufferManager screen_buffer_manager );

			std::cout << r2tm::split;

			{
				std::cout << r2tm::tab << "[ESC] End" << r2tm::linefeed;
				std::cout << r2tm::tab << "[Any Key] screen_buffer_manager.Swap();" << r2tm::linefeed;
			}

			std::cout << r2tm::split;

			{
				int key_code = -1;
				do
				{
					key_code = _getch();
					if( 27 == key_code )
					{
						break;
					}

					screen_buffer_manager.Swap();

				} while( true );
			}

			return r2tm::eDoLeaveAction::Pause;
		};
	}
}