#include "r2bix_input_MachineInputCollector.h"

namespace r2bix_input
{
	MachineInputCollector::MachineInputCollector( const int offset_x, const int offset_y ) :
			mOffset( offset_x, offset_y )
		,	mObservationKeyList()
		,	mObservationKeyStates()
		,	mCursorPoint_Last()
		,	mCursorPoint()
		,	mbMouseMoved( false )
	{
		mObservationKeyList.fill( 0 );
	}

	MachineInputCollector::MachineInputCollector( const r2::PointInt offset ) :
		mOffset( offset.GetX(), offset.GetY() )
		, mObservationKeyList()
		, mObservationKeyStates()
		, mCursorPoint_Last()
		, mCursorPoint()
		, mbMouseMoved( false )
	{
		mObservationKeyList.fill( 0 );
	}

	void MachineInputCollector::Collect()
	{
		if( !HasWindowFocus() )
		{
			//
			// Key : Keyboard, Mouse
			//
			{
				int key_value = 0;
				for( unsigned char i = 0x01, end = static_cast< unsigned char >( mObservationKeyList.size() ); end > i; ++i )
				{
					mObservationKeyStates[i] = false;
				}
			}

			//
			// Mouse Position
			//
			{
				mCursorPoint_Last = mCursorPoint;
				mbMouseMoved = false;
			}
		}
		else
		{
			//
			// Key : Keyboard, Mouse
			//
			{
				int key_value = 0;
				for( unsigned char i = 0x01, end = static_cast< unsigned char >( mObservationKeyList.size() ); end > i; ++i )
				{
					if( 0 == mObservationKeyList[i] )
					{
						continue;
					}

					key_value = GetKeyState( i );

					mObservationKeyStates[i] = key_value & 0x8000;
				}
			}

			//
			// Mouse Position
			//
			{
				mCursorPoint_Last = mCursorPoint;
				mCursorPoint = ( r2bix_input::GetCursorPoint() - mOffset );
				mbMouseMoved = ( mCursorPoint_Last != mCursorPoint );
			}
		}
	}



	void MachineInputCollector::AddObservationKeys( const ObservationKeys& observation_keys )
	{
		for( const auto k : observation_keys )
		{
			++mObservationKeyList[k];
		}
	}
	void MachineInputCollector::RemoveObservationKeys( const ObservationKeys& observation_keys )
	{
		for( const auto k : observation_keys )
		{
			--mObservationKeyList[k];
		}
	}
}