#include "pch.h"
#include "visible_resource_test.h"

#include <Windows.h>

#include "base/r2_eTestResult.h"

#include "renderer/r2_Camera.h"
#include "renderer/r2_iRenderable.h"

namespace visible_resource_test
{
	r2::iTest::TitleFunc FillAll::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Fill All";
		};
	}
	r2::iTest::DoFunc FillAll::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2::VisibleResource visible_resource( 30, 20, '0' );

			std::size_t x = 0;
			for( const char element : visible_resource )
			{
				std::cout << element;

				++x;
				if( visible_resource.GetWidth() <= x )
				{
					x = 0u;
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc Fill::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Fill";
		};
	}
	r2::iTest::DoFunc Fill::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()() << " #" << r2::linefeed;

			std::cout << r2::split;

			r2::VisibleResource visible_resource( 30, 20 );
			visible_resource.Fill( 0, 0, '0' );
			visible_resource.Fill( visible_resource.GetWidth() - 1u, 0, '0' );
			visible_resource.Fill( visible_resource.GetWidth() - 1u, visible_resource.GetHeight() - 1u, '0' );
			visible_resource.Fill( 0, visible_resource.GetHeight() - 1u, '0' );

			std::size_t x = 0;
			for( const char element : visible_resource )
			{
				std::cout << element;

				++x;
				if( visible_resource.GetWidth() <= x )
				{
					x = 0u;
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	r2::iTest::TitleFunc DrawWithPosition::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Draw With Position";
		};
	}
	r2::iTest::DoFunc DrawWithPosition::GetDoFunction()
	{
		return []()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			const r2::VisibleResource visible_resource( 10, 10, '0' );

			HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
			COORD pos = { 10, 5 };
			SetConsoleCursorPosition( stdHandle, pos );

			int count = 0;
			for( const char element : visible_resource )
			{
				std::cout << element;

				++count;
				if( visible_resource.GetWidth() <= count )
				{
					count = 0;
					pos.Y += 1;
					SetConsoleCursorPosition( stdHandle, pos );
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	InitWithChars::InitWithChars() :
		mVisibleResource1( "Init With Chars" )
		, mVisibleResource2( 5, "aaaaaaaaabbbbbbbbbbcccccdddddddeeeeeeeeeeeeeeeefffggg" )
	{}

	r2::iTest::TitleFunc InitWithChars::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Init With Chars";
		};
	}
	r2::iTest::DoFunc InitWithChars::GetDoFunction()
	{
		const auto& vr1 = GetInstance().mVisibleResource1;
		const auto& vr2 = GetInstance().mVisibleResource2;

		return [vr1, vr2]()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			std::size_t x = 0;

			{
				for( const char element : vr1 )
				{
					std::cout << element;

					++x;
					if( vr1.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
			}

			std::cout << r2::split;

			{
				x = 0;
				for( const char element : vr2 )
				{
					std::cout << element;

					++x;
					if( vr2.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}



	VisibleRect::VisibleRect() :
		mVisibleResource( 5, "aaaaaaaaabbbbbbbbbbcccccdddddddeeeeeeeeeeeeeeeefffggg" )
	{}

	r2::iTest::TitleFunc VisibleRect::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Visible Resource - Visible Rect";
		};
	}
	r2::iTest::DoFunc VisibleRect::GetDoFunction()
	{
		auto visible_rect = GetInstance().mVisibleResource.GetVisibleRect();
		visible_rect.SetOrigin( visible_rect.GetOrigin().GetX() + 2, visible_rect.GetOrigin().GetY() + 1 );
		visible_rect.SetSize( visible_rect.GetSize().GetWidth() - 2, visible_rect.GetSize().GetHeight() - 1 );
		GetInstance().mVisibleResource.SetVisibleRect( visible_rect );


		return [&vr = GetInstance().mVisibleResource]()->r2::eTestResult
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				std::size_t x = 0;
				for( const char element : vr )
				{
					std::cout << element;

					++x;
					if( vr.GetWidth() <= x )
					{
						x = 0u;
						std::cout << r2::linefeed;
					}
				}
				if( 0u != x )
				{
					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			{
				for( int y = vr.GetVisibleRect().GetMinY(); y < vr.GetVisibleRect().GetMaxY(); ++y )
				{
					for( int x = vr.GetVisibleRect().GetMinX(); x < vr.GetVisibleRect().GetMaxX(); ++x )
					{
						std::cout << vr.Get( x, y );
					}

					std::cout << r2::linefeed;
				}
			}

			std::cout << r2::split;

			return r2::eTestResult::RunTest;
		};
	}
}