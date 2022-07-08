#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class ActionMenu
{
private:
	ActionMenu() = delete;

public:
	static const char* GetTitle() { return "Action Menu"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};