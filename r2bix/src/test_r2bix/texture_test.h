#pragma once

#include "r2cm/r2cm_iItem.h"
#include "base/r2base_Singleton.h"

namespace texture_test
{
	class FillAll : public r2cm::iItem, public r2::SingleTon<FillAll>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class Fill : public r2cm::iItem, public r2::SingleTon<Fill>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};

	class InitWithChars_1 : public r2cm::iItem, public r2::SingleTon<InitWithChars_1>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_2 : public r2cm::iItem, public r2::SingleTon<InitWithChars_2>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_3 : public r2cm::iItem, public r2::SingleTon<InitWithChars_3>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
	class InitWithChars_4 : public r2cm::iItem, public r2::SingleTon<InitWithChars_4>
	{
	public:
		TitleFunc GetTitleFunction() const override;
		DoFunc GetDoFunction() override;
	};
}