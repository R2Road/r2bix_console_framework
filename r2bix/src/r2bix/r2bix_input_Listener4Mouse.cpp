#include "r2bix_input_Listener4Mouse.h"

#include "r2_Assert.h"

namespace r2bix_input
{
	Listener4Mouse::Listener4Mouse() :
		  mOrder( 0 )
		, mbMousePositionUse( false)
		, mCursorPoint_Current()
		, mCursorPoint_Last()
		, mObservationKeyContainer()

		, mCallback4CursorMoved()
		, mCallback4KeyStatusChanged()
	{}
	Listener4Mouse::Listener4Mouse( const int order ) :
		mOrder( order )
		, mbMousePositionUse()
		, mCursorPoint_Current()
		, mCursorPoint_Last()
		, mObservationKeyContainer()

		, mCallback4CursorMoved()
		, mCallback4KeyStatusChanged()
	{}



	void Listener4Mouse::SetCallback4CursorMoved( const Callback4CursorMovedT& callback )
	{
		if( callback )
		{
			mbMousePositionUse = true;
		}
		else
		{
			mbMousePositionUse = false;
		}

		mCallback4CursorMoved = callback;
	}
	void Listener4Mouse::SetCallback4KeyStatusChanged( const Callback4KeyStatusChangedT& callback )
	{
		mCallback4KeyStatusChanged = callback;
	}
	void Listener4Mouse::AddObservationKey( const r2bix_input::eKeyCode key_code )
	{
		if( key_code != r2bix_input::eKeyCode::VK_LBUTTON && key_code != r2bix_input::eKeyCode::VK_RBUTTON && key_code != r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Mouse : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyContainer.Add( key_code );
	}



	bool Listener4Mouse::UpdateCursor( const r2bix_input::CursorPoint cursor_point )
	{
		if( mbMousePositionUse )
		{
			mCursorPoint_Last = mCursorPoint_Current;
			mCursorPoint_Current = cursor_point;

			if( mCallback4CursorMoved )
			{
				return mCallback4CursorMoved( cursor_point );
			}
		}

		return false;
	}
	void Listener4Mouse::UpdateKey( const int key_index, const bool key_flag )
	{
		if( key_flag )
		{
			switch( mObservationKeyContainer[key_index].key_status )
			{
			case eKeyStatus::None:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Push;
				mCallback4KeyStatusChanged( key_index, mObservationKeyContainer[key_index].key_status );
				break;

			case eKeyStatus::Push:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Pressed;
				mCallback4KeyStatusChanged( key_index, mObservationKeyContainer[key_index].key_status );
				break;

			//case eKeyStatus::Pressed:
			//	break;

			}
		}
		else
		{
			switch( mObservationKeyContainer[key_index].key_status )
			{
			//case eKeyStatus::None:
			//	break;

			case eKeyStatus::Push:
			case eKeyStatus::Pressed:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Release;
				mCallback4KeyStatusChanged( key_index, mObservationKeyContainer[key_index].key_status );
				break;

			case eKeyStatus::Release:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::None;
				mCallback4KeyStatusChanged( key_index, mObservationKeyContainer[key_index].key_status );
				break;
			}
		}
	}
}