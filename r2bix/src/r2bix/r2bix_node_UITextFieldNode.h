#pragma once

#include "r2bix_node_Node.h"

namespace r2bix
{
	class Director;
}

namespace r2bix_node
{
	class UITextFieldNode
	{
	private:
		UITextFieldNode() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}