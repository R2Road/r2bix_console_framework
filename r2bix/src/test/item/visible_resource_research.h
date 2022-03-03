#pragma once

#include "test/r2test_iTest.h"
#include "base/r2base_Singleton.h"

namespace visible_resource_research
{
	class DrawWithPosition : public r2test::iTest, public r2base::SingleTon<DrawWithPosition>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}