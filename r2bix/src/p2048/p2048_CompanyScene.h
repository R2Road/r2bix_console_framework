#pragma once

#include <memory>

#include "game/r2game_Scene.h"
#include "render/r2render_Camera.h"
#include "render/r2render_Texture.h"

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace r2game
{
	class LabelNode;
}

namespace r2render
{
	class Camera;
}

namespace p2048
{
	class CompanyScene : public r2game::Scene
	{
	private:
		CompanyScene( r2base::Director& director );

	public:
		static r2base::NodeUp Create( r2base::Director& director );

	private:
		bool Init() override;
	public:
		void Update() override;

	private:
		r2render::Camera mCamera;
		r2render::Texture mRenderTarget;

		r2game::LabelNode* mLabelNode;
	};
}