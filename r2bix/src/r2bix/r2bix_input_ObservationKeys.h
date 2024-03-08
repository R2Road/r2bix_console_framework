#pragma once

#include <vector>

#include "r2bix_input_Constant.h"

namespace r2bix_input
{
	class ObservationKeys
	{
	public:
		using ContainerT = std::vector<KeyCodeTypeT>;
		using ConstIteratorT= ContainerT::const_iterator;


		//
		//
		//
		ObservationKeys( std::initializer_list<uint8_t> list ) : mContainer( list )
		{}


		//
		//
		//
		ConstIteratorT begin() const
		{
			return mContainer.begin();
		}
		ConstIteratorT end() const
		{
			return mContainer.end();
		}


		//
		//
		//
		KeyCodeTypeT operator[]( const unsigned char key_index ) const
		{
			return mContainer[key_index];
		}


	private:
		ContainerT mContainer;
	};
}