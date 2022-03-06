#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class ComponentMenu
{
private:
	ComponentMenu() = delete;

public:
	static const char* GetTitle() { return "Component"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};