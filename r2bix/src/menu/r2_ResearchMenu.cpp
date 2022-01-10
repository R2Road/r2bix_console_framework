#include "pch.h"
#include "r2_ResearchMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"
#include "r2_RootMenu.h"

namespace r2
{
	MenuUp ResearchMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle(),
			"\n" "> ..."
		) );

		{
			//ret->AddChild( '1', key_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->eTestResult
				{
					director.Setup( r2::RootMenu::Create( director ) );
					return eTestResult::ChangeScene;
				}
			);
		}

		return ret;
	}
}