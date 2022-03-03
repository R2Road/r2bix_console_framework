#include "pch.h"
#include "r2test_Utility.h"

#include <Windows.h>

namespace r2test
{
	void Utility::DrawRect( const int offset_y, const r2::RectInt& rect, const char c )
	{
		HANDLE stdHandle = GetStdHandle( STD_OUTPUT_HANDLE );

		for( int y = rect.GetMinY(); rect.GetMaxY() >= y; ++y )
		{
			for( int x = rect.GetMinX(); rect.GetMaxX() >= x; ++x )
			{
				SetConsoleCursorPosition( stdHandle, { static_cast<short>( x ), static_cast<short>( offset_y + y ) } );

				std::cout << c;
			}
		}
	}
}