#include "InputMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test/test_r2bix/item/key_code_viewer.h"
#include "test/test_r2bix/item/window_input_test.h"

#include "test/test_r2bix/R2bixMenu.h"

r2cm::MenuUp InputMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', key_code_viewer::Basic() );


		ret->AddLineFeed();


		ret->AddItem( 'q', window_input_test::KeyStatus() );
		ret->AddItem( 'w', window_input_test::TestKeyboardInputCollector() );


		ret->AddSplit();


		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}