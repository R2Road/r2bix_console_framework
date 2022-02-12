#include "pch.h"
#include "r2test_FrameBufferMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_RootMenu.h"

#include "scene/TestScene.h"

#include "test/framebuffer_test.h"

namespace r2test
{
	r2base::NodeUp FrameBufferMenu::Create( r2base::Director& director )
	{
		r2base::MenuUp ret( new ( std::nothrow ) r2base::TestMenu(
			director
			, GetTitle(),
			"> ..."
		) );

		{
			ret->AddChild( '1', framebuffer_test::Basic::GetInstance() );
			ret->AddChild( '2', framebuffer_test::DrawAtOnce::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RootMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}