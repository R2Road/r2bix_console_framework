#pragma once

#include <vector>

#include "r2/r2_Direction4.h"
#include "r2/r2_GridIndexConverter.h"

namespace p2048
{
	class Stage
	{
	public:
		using ContainerT = std::vector<int>;

		Stage( const uint32_t width, const uint32_t height );

		//
		// Getter
		//
		uint32_t GetWidth() const { return mGridIndexConverter.GetWidth(); }
		uint32_t GetHeight() const { return mGridIndexConverter.GetHeight(); }
		uint32_t GetMaxX() const { return mGridIndexConverter.GetWidth() - 1; }
		uint32_t GetMaxY() const { return mGridIndexConverter.GetHeight() - 1; }
		uint32_t Get( const uint32_t x, const uint32_t y ) const;

		//
		//
		//
		void ClearAll();
		void Add( const uint32_t x, const uint32_t y, const uint32_t val );
		void Remove( const uint32_t x, const uint32_t y );

		//
		//
		//
		void Move( const r2::Direction4::eState direction_state );

	private:
		r2::GridIndexConverter mGridIndexConverter;
		ContainerT mContainer;
	};
}