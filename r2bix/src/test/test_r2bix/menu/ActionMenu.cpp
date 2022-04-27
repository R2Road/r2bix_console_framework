#include "pch.h"
#include "ActionMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test/test_r2bix/TestR2bixRootMenu.h"

#include "test/test_r2bix/item/action_test.h"

r2cm::MenuUp ActionMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', action_test::TickActionTest::GetInstance() );
		ret->AddItem( '2', action_test::DelayActionTest::GetInstance() );
		ret->AddItem( '3', action_test::SequenceActionTest::GetInstance() );
		ret->AddItem( '4', action_test::MoveByActionTest::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'q', action_test::RepeatActionTest::GetInstance() );
		ret->AddItem( 'w', action_test::BlinkActionTest::GetInstance() );
		ret->AddItem( 'e', action_test::CallbackActionTest::GetInstance() );
		ret->AddItem( 'r', action_test::AnimationRequestActionTest::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eTestEndAction
			{
			director.Setup( TestR2bixRootMenu::Create( director ) );
			return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}