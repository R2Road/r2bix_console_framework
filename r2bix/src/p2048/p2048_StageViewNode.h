#pragma once

#include "r2bix/r2base_Node.h"

namespace r2bix
{
	class Director;
}

namespace p2048
{
	class StageViewNode : public r2bix_node::Node
	{
	private:
		StageViewNode() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}