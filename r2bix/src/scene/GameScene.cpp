#include "pch.h"
#include "GameScene.h"

#include "base/r2base_Director.h"

GameScene::GameScene( r2base::Director& director ) : r2game::Node( director )
{}

bool GameScene::Do()
{
	return true;
}