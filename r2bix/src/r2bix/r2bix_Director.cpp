#include "r2bix_Director.h"

#include <utility> // std::move

#include "r2bix_node_SceneNode.h"

namespace r2bix
{
	Director::Director( const r2bix_director::Config& director_config ) :
		mScreenBufferManager( director_config.ScreenBufferOffset_X, director_config.ScreenBufferOffset_Y )
		, mScheduler( director_config, std::bind( &Director::onUpdate, this, std::placeholders::_1 ), std::bind( &Director::onRender, this ) )
		, mbAbort( false )
		, mScreenBufferSIze( director_config.ScreenBufferSize_Width, director_config.ScreenBufferSize_Height )

		, mInputManager( director_config.ScreenBufferOffset_X, director_config.ScreenBufferOffset_Y )

		, mCurrentSceneNode()
		, mNextSceneNode()
	{}

	void Director::Setup( r2bix_node::SceneNodeUp node )
	{
		if( mCurrentSceneNode )
		{
			mNextSceneNode = std::move( node );
		}
		else
		{
			mCurrentSceneNode = std::move( node );
		}
	}

	void Director::Run()
	{
		ClearScreen();

		while( !mbAbort )
		{
			if( mNextSceneNode )
			{
				mCurrentSceneNode->Terminate();
				mCurrentSceneNode = std::move( mNextSceneNode );
			}

			mScheduler.Do();
		}
	}
	void Director::onUpdate( const float delta_time )
	{
		mInputManager.Update();

		mCurrentSceneNode->Update( delta_time );
	}
	void Director::onRender()
	{
		mCurrentSceneNode->Render();

		mScreenBufferManager.InitCursor();
		mScreenBufferManager.Swap();
	}

	void Director::Terminate()
	{
		if( mCurrentSceneNode )
		{
			mCurrentSceneNode->Terminate();
		}
	}



	void Director::ClearScreen()
	{
		mScreenBufferManager.ClearCurrentBuffer();
	}

	void Director::Write2BackBuffer( const r2bix_render::Texture* const texture )
	{
		mScreenBufferManager.Write2BackBuffer( texture );
	}
}