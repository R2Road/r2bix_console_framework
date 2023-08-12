#pragma once

#include "r2_NoneCopyable.h"
#include "r2_Rect.h"

#include "r2tm/r2tm_WindowUtility.h"

namespace r2helper
{
	class TMPrinter4RectGuide : private r2::NoneCopyable
	{
	private:
		TMPrinter4RectGuide() = delete;

	public:
		template<typename T>
		inline static void Print( r2tm::WindowUtility::CursorPoint pivot, const short offset_x, const short offset_y, uint16_t space_h, uint16_t space_v, const r2::Rect<T>& rect, const char c )
		{
			//
			//
			//
			pivot.x += offset_x;
			pivot.y += offset_y;

			//
			//
			//
			space_h = ( space_h > 0 ? space_h : 1 );
			space_v = ( space_v > 0 ? space_v : 1 );

			//
			// Draw
			//
			const r2::Rect<T> inner_rect(
				  rect.GetMinX() + 1, rect.GetMinY() + 1
				, rect.GetSize().GetWidth() - 2, rect.GetSize().GetHeight() - 2
			);
			for( T y = rect.GetMinY(), ey = rect.GetMaxY(); ey >= y; ++y )
			{
				for( T x = rect.GetMinX(), ex = rect.GetMaxX(); ex >= x; ++x )
				{
					if( inner_rect.IsIn( x, y ) )
					{
						continue;
					}

					r2tm::WindowUtility::FillCharacter(
						{
								static_cast<short>( pivot.x + ( x * space_h ) )
							,	static_cast<short>( pivot.y + ( y * space_v ) )
						}
						, c
					);
				}
			}

			//
			// Move Cursor
			//
			r2tm::WindowUtility::MoveCursorPoint( {
					0
				,	static_cast<short>( pivot.y + ( rect.GetMaxY() * space_v ) + 1 )
			} );
		}

		template<typename T>
		inline static void Print( const short offset_x, const short offset_y, uint16_t space_h, uint16_t space_v, const r2::Rect<T>& rect, const char c )
		{
			const auto pivot_point = r2tm::WindowUtility::GetCursorPoint();
			Print( pivot_point, offset_x, offset_y, space_h, space_v, rect, c );
		}

		template<typename T>
		inline static void Print( const short offset_x, const short offset_y, const r2::Rect<T>& rect, const char c )
		{
			Print( offset_x, offset_y, 2, 1, rect, c );
		}

		template<typename T>
		inline static void Print( const r2::Rect<T>& rect, const char c )
		{
			Print( 0, 0, 2, 1, rect, c );
		}

		template<typename T>
		inline static void Print( const r2tm::WindowUtility::CursorPoint& cursor_point, const short offset_x, const short offset_y, const r2::Rect<T>& rect, const char c )
		{
			Print( cursor_point, offset_x, offset_y, 2, 1, rect, c );
		}
		template<typename T>
		inline static void Print( const r2tm::WindowUtility::CursorPoint& cursor_point, const r2::Rect<T>& rect, const char c )
		{
			Print( cursor_point, 0, 0, 2, 1, rect, c );
		}

		template<typename T>
		inline static void Print( const r2tm::WindowUtility::CursorPoint& cursor_point, const typename r2::Size<T>& size, const char c )
		{
			Print( cursor_point, 0, 0, 2, 1, r2::Rect<T>{ 0, 0, size.GetWidth() - 1, size.GetHeight() - 1 }, c );
		}
	};
}