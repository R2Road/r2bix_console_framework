#include "pch.h"
#include "r2game_RootScene.h"

#include <conio.h>

#include "base/r2base_Director.h"

#include "scene/DevelopScene.h"
#include "scene/GameScene.h"

namespace r2game
{
	RootScene::RootScene( r2base::Director& director ) : GameScene( director )
	{}

	r2base::NodeUp RootScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) RootScene( director ) );
		return ret;
	}

	bool RootScene::Do()
	{
		std::cout << "# " << "Empty Game Scene" << " #" << r2::linefeed;

		auto input = _getch();
		if( 27 == input )
		{
			mDirector.Setup( DevelopScene::Create( mDirector ) );
		}

		system( "cls" );

		return true;
	}
}