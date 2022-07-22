#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class TestMainMenu
{
private:
	TestMainMenu() = delete;

public:
	static const char* GetTitle() { return "Test Main"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};