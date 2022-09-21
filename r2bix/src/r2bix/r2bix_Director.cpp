#include "r2bix_Director.h"

#include <utility> // std::move

#include "r2node_SceneNode.h"

namespace r2bix
{
	Director::Director( const r2bix_director::Config& director_config ) :
		mScreenBufferManager()
		, mUpdateTimer( director_config.UpdateFramePerSeconds )
		, mRenderTimer( director_config.RenderFramePerSeconds )
		, mbAbort( false )
		, mScreenBufferSIze( director_config.ScreenBufferSIze )

		, mKeyboardInputCollector()

		, mCurrentSceneNode()
		, mNextSceneNode()
	{}

	void Director::Setup( r2node::SceneNodeUp node )
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
				mCurrentSceneNode = std::move( mNextSceneNode );
			}

			if( mUpdateTimer.Update() )
			{
				mKeyboardInputCollector.Collect();

				mCurrentSceneNode->Update( mUpdateTimer.GetElapsedTime() );
			}

			if( mRenderTimer.Update() )
			{
				mCurrentSceneNode->Render();

				mScreenBufferManager.InitCursor();
				mScreenBufferManager.Swap();
			}
		}
	}

	void Director::ClearScreen()
	{
		mScreenBufferManager.ClearCurrentBuffer();
	}

	void Director::Write2BackBuffer( const r2render::Texture* const texture )
	{
		mScreenBufferManager.Write2BackBuffer( texture );
	}

	void Director::AddInputListener( r2input::KeyboardInputListener* const keyboard_input_listener )
	{
		mKeyboardInputCollector.AddListener( keyboard_input_listener );
	}
	void Director::RemoveInputListener( r2input::KeyboardInputListener* const keyboard_input_listener )
	{
		mKeyboardInputCollector.RemoveListener( keyboard_input_listener );
	}
}