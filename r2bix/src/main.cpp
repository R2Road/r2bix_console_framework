﻿#if defined( DEBUG ) || defined( _DEBUG )
	#include "vld/include/vld.h"
#endif

#include "r2bix_VersionInfo.h"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_WindowUtility.h"

#include "DevelopmentMenu.h"

int main()
{
	//
	// Environment : Title
	//
	r2tm::WindowUtility::ChangeTitle( r2bix::VersionInfo.String4Version );

	//
	// Environment : Size
	//
	r2tm::WindowUtility::Resize( 960, 960 );

	//
	// Environment : Position
	//
	r2tm::WindowUtility::Move( 0, 0 );

	//
	// Setup
	//
	r2tm::Director director;
	director.Setup( DevelopmentMenu() );

	//
	// Process
	//
	director.Run();

	return 0;
}
