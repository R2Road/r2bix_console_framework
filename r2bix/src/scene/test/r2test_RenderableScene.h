#pragma once

#include <memory>

namespace r2base
{
	class Director;
}

namespace r2node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;
}

namespace r2test
{
	class RenderableScene
	{
	private:
		RenderableScene() = delete;

	public:
		static const char* GetTitle() { return "Renderable"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );
	};
}