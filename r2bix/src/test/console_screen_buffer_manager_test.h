#pragma once

#include "base/r2base_iTest.h"
#include "base/r2base_Singleton.h"

namespace console_screen_buffer_manager_test
{
	class MakeSecondBuffer : public r2base::iTest, public r2base::SingleTon<MakeSecondBuffer>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};	
}