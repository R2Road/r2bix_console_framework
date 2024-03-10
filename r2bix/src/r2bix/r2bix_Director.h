#pragma once

#include <memory>

#include "r2bix_director_ScreenBufferManager.h"
#include "r2bix_input_InputManager.h"
#include "r2bix_node_SceneNode.h"
#include "r2_SizeInt.h"

#include "r2bix_director_Config.h"
#include "r2bix_director_Scheduler.h"

namespace r2bix
{
	class Director
	{
	public:
		Director( const r2bix_director::Config& director_config );

		void Setup( r2bix_node::SceneNodeUp node );

		void Run();
	private:
		void onUpdate( const float delta_time );
		void onRender();

	public:
		//
		//
		//
		r2::SizeInt GetScreenBufferSize() const
		{
			return mScreenBufferSIze;
		}

		//
		//
		//
		void RequestAbort() { mbAbort = true; }
		void ClearScreen();
		void Write2BackBuffer( const r2bix_render::Texture* const texture );

		//
		// Input
		//
		r2bix_input::InputManager& GetInputManager()
		{
			return mInputManager;
		}

	private:
		r2bix_director::ScreenBufferManager mScreenBufferManager;
		r2bix_director::Scheduler mScheduler;
		bool mbAbort;
		r2::SizeInt mScreenBufferSIze;

		r2bix_input::InputManager mInputManager;

		r2bix_node::SceneNodeUp mCurrentSceneNode;
		r2bix_node::SceneNodeUp mNextSceneNode;
	};
}