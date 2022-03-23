#include "pch.h"
#include "TestMainMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test/test_p2048/TestP2048RootMenu.h"
#include "test/test_r2bix/TestRootMenu.h"

r2cm::MenuUp TestMainMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> To do : ..."
	) );

	{
		ret->AddItem(
			'1'
			, []()->const char* { return TestRootMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'2'
			, []()->const char* { return TestP2048RootMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestP2048RootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Develop Menu"; }
			, []()->r2cm::eTestEndAction
			{
				return r2cm::eTestEndAction::Exit;
			}
		);
	}

	return ret;
}