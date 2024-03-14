#pragma once

#include <vector>

#include "r2bix_input_Constant.h"

namespace r2bix_input
{
	class ObservationKeys
	{
	public:
		using KeyValueT = KeyCodeTypeT;
		using ContainerT = std::vector<KeyValueT>;
		using ConstIteratorT= ContainerT::const_iterator;


		//
		//
		//
		ObservationKeys() : mContainer()
		{}
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
		KeyCodeTypeT& operator[]( const std::size_t key_index )
		{
			return mContainer[key_index];
		}
		const KeyCodeTypeT& operator[]( const std::size_t key_index ) const
		{
			return mContainer[key_index];
		}


		//
		//
		//
		void Add( const KeyValueT key_value )
		{
			mContainer.push_back( key_value );
		}


	private:
		ContainerT mContainer;
	};
}