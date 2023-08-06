#pragma once

#include <memory>

#include "r2bix_node_SceneNode.h"

namespace p_mini_adv
{
	class GameScene : public r2bix_node::SceneNode
	{
	private:
		GameScene( r2bix::Director& director );

	public:
		static const char* const GetTitle() { return "Game : Mini Adventure( In Progress )"; }
		static r2bix_node::SceneNodeUp Create( r2bix::Director& director );

	private:
		bool Init() override;
	public:
		void Update( const float delta_time ) override;
	};
}