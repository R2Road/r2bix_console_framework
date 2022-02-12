#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

namespace window_input_test
{
	class TestKeyboardInputCollector : public r2base::iTest, public r2base::SingleTon<TestKeyboardInputCollector>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}