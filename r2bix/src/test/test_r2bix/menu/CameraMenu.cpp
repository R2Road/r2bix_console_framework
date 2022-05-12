#include "CameraMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_constant.h"

#include "test/test_r2bix/TestR2bixRootMenu.h"

#include "test/test_r2bix/item/camera_test.h"

r2cm::MenuUp CameraMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> 카메라는 무언가를 할 필요 없다."
		"\n"	"> 요구하는 위치에 자리하고, 그 데이터를 잘 가지고만 있으면 된다."
		"\n"	"> 뭐 하려고 하지마."
	) );

	{
		ret->AddItem( '1', camera_test::CameraPosition::GetInstance() );
		ret->AddItem( '2', camera_test::CameraRect::GetInstance() );
		ret->AddItem( '3', camera_test::CameraMove::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eItemLeaveAction
			{
				director.Setup( TestR2bixRootMenu::Create( director ) );
				return r2cm::eItemLeaveAction::None;
			}
		);
	}

	return ret;
}