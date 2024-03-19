#include "r2bix_input_Listener4Keyboard.h"

namespace r2bix_input
{
	Listener4Keyboard::Listener4Keyboard() :
		  mOrder( 0 )
		, mObservationKeyContainer()
		, mKeyStatusContainer()
	{}
	Listener4Keyboard::Listener4Keyboard( const int order, std::initializer_list<uint8_t> list ) :
		  mOrder( order )
		, mObservationKeyContainer( list )
		, mKeyStatusContainer( list.size(), eKeyStatus::None )
	{}

	void Listener4Keyboard::Update( const ObservationKeyStatesT& observation_key_states )
	{
		for( std::size_t i = 0u, end = mKeyStatusContainer.size(); end > i; ++i )
		{
			if( observation_key_states.test( mObservationKeyContainer[i]) )
			{
				switch( mKeyStatusContainer[i] )
				{
				case eKeyStatus::None:
					mKeyStatusContainer[i] = eKeyStatus::Push;
					break;

				case eKeyStatus::Push:
					mKeyStatusContainer[i] = eKeyStatus::Pressed;
					break;

				//case eKeyStatus::Pressed:
				//	break;

				}
			}
			else
			{
				switch( mKeyStatusContainer[i] )
				{
				//case eKeyStatus::None:
				//	break;

				case eKeyStatus::Push:
				case eKeyStatus::Pressed:
					mKeyStatusContainer[i] = eKeyStatus::Release;
					break;

				case eKeyStatus::Release:
					mKeyStatusContainer[i] = eKeyStatus::None;
					break;
				}
			}
		}
	}
}