#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;

	class CameraMenu
	{
	private:
		CameraMenu() = delete;

	public:
		static const char* GetTitle() { return "Camera"; }
		static MenuUp Create( Director& director );
	};
}