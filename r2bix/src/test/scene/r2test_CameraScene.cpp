#include "pch.h"
#include "r2test_CameraScene.h"

#include "base/r2base_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "r2test_RootScene.h"
#include "TestScene.h"

#include "test/item/camera_test.h"

namespace r2test
{
	r2node::SceneNodeUp CameraScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
					"> 카메라는 무언가를 할 필요 없다."
			"\n"	"> 요구하는 위치에 자리하고, 그 데이터를 잘 가지고만 있으면 된다."
			"\n"	"> 뭐 하려고 하지마."
		) );

		{
			ret->AddChild( '1', camera_test::CameraPosition::GetInstance() );
			ret->AddChild( '2', camera_test::CameraRect::GetInstance() );
			ret->AddChild( '3', camera_test::CameraMove::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]( r2base::Director& )->r2base::eTestEndAction
				{
					director.Setup( r2test::RootScene::Create( director ) );
					return r2base::eTestEndAction::None;
				}
			);
		}

		return ret;
	}
}