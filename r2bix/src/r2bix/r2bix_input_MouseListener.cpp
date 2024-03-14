#include "r2bix_input_MouseListener.h"

namespace r2bix_input
{
	MouseListener::MouseListener() :
		  mbMousePositionUse( false)
		, mObservationKeys()
		, mKeyStatusContainer()
	{}
	MouseListener::MouseListener( const bool position_use, const bool left_click, const bool right_click ) :
		  mbMousePositionUse( position_use )
		, mObservationKeys()
		, mKeyStatusContainer()
	{
		if( left_click )
		{
			mObservationKeys.Add( r2bix_input::eKeyCode::VK_LBUTTON );
		}
		if( right_click )
		{
			mObservationKeys.Add( r2bix_input::eKeyCode::VK_RBUTTON );
		}

		mKeyStatusContainer.resize( mObservationKeys.Size(), eKeyStatus::None );
	}

	void MouseListener::Update( const ObservationKeyStatesT& observation_key_states )
	{
		for( std::size_t i = 0u, end = mKeyStatusContainer.size(); end > i; ++i )
		{
			if( observation_key_states.test( mObservationKeys[i]) )
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