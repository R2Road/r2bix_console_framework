﻿#include "pch.h"

#include <conio.h>

#if defined( DEBUG ) || defined( _DEBUG )
	#include <vld.h>
#endif

#include "base/r2base_Director.h"
#include "p2048/p2048_EntryScene.h"
#include "p2048mini/p2048mini_GameScene.h"
#include "pmr/pmr_CompanyScene.h"

#include "r2cm/r2cm_Director.h"
#include "test/TestMainMenu.h"

#include "utility/r2utility_WindowUtil.h"

int main()
{
	//
	// Environment : Title
	//
	r2utility::ChangeWindowTitle( L"r2bix" );

	//
	// Environment : Size
	//
	r2utility::ResizeWindow( 960, 960 );

	//
	// Environment : Position
	//
	r2utility::MoveWindow( 0, 0 );

	bool bRun = true;
	do
	{
		system( "cls" );

		std::cout << "# Develop #" << r2::linefeed;

		std::cout << r2::split;

		std::cout << "+ Menu" << r2::linefeed2;

		std::cout << "[ESC] " "Exit" << r2::linefeed2;

		std::cout << "[1] " "Test" << r2::linefeed;
		std::cout << "[2] " << p2048mini::GameScene::GetTitle() << r2::linefeed;
		std::cout << "[3] " << p2048::EntryScene::GetTitle() << r2::linefeed;
		std::cout << "[4] " << pmr::CompanyScene::GetTitle() << r2::linefeed;

		std::cout << r2::split;

		std::cout << "Select Menu";

		const auto input = _getch();
		switch( input )
		{
		case '1':
		{
			//
			// Setup
			//
			r2cm::Director director;
			director.Setup( TestMainMenu::Create( director ) );

			//
			// Process
			//
			director.Run();
		}
		break;

		case '2':
		{
			//
			// Setup
			//
			r2base::Director director;
			director.Setup( p2048mini::GameScene::Create( director ) );

			//
			// Process
			//
			director.Run();
		}
		break;
		case '3':
		{
			//
			// Setup
			//
			r2base::Director director;
			director.Setup( p2048::EntryScene::Create( director ) );

			//
			// Process
			//
			director.Run();
		}
		break;

		case '4':
		{
			//
			// Setup
			//
			r2base::Director director;
			director.Setup( pmr::CompanyScene::Create( director ) );

			//
			// Process
			//
			director.Run();
		}
		break;

		case 27:
			bRun = false;
			break;
		}

	} while( bRun );

	return 0;
}
