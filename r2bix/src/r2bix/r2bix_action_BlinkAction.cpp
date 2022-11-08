#include "r2bix_action_BlinkAction.h"

#include "r2bix_node_Node.h"

namespace r2bix_action
{
	BlinkAction::BlinkAction() :
		mbLastVisible( false )
		, mTimer( 1.f )
	{}

	std::unique_ptr<BlinkAction> BlinkAction::Create()
	{
		std::unique_ptr<BlinkAction> ret( new ( std::nothrow ) BlinkAction() );
		return ret;
	}

	void BlinkAction::Enter()
	{
		mbLastVisible = mOwnerNode->IsVisible();
		mOwnerNode->SetVisible( !mbLastVisible );

		mTimer.Start();
	}
	bool BlinkAction::Update( const float delta_time )
	{
		if( !mTimer.Update( delta_time ) )
		{
			mOwnerNode->SetVisible( mbLastVisible );
		}

		return mTimer.IsAlive();
	}
}