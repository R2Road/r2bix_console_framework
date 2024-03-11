#include "r2bix_input_InputManager.h"

#include "r2bix_input_KeyboardInputListener.h"

namespace r2bix_input
{
	InputManager::InputManager() :
		  mMachineInputCollector()
		, mKeyboardInputListener( nullptr )
	{}

	void InputManager::Update()
	{
		//
		// 입력 수집
		//
		mMachineInputCollector.Collect();

		//
		// 키 상태 업데이트
		//
		if( mKeyboardInputListener )
		{
			mKeyboardInputListener->Update( mMachineInputCollector.GetObservationKeyStates() );
		}
	}



	void InputManager::AddInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener )
	{
		RemoveInputListener( mKeyboardInputListener );

		mKeyboardInputListener = keyboard_input_listener;

		mMachineInputCollector.AddObservationKeys( mKeyboardInputListener->GetObservationKeys() );
	}
	void InputManager::RemoveInputListener( r2bix_input::KeyboardInputListener* const keyboard_input_listener )
	{
		if( nullptr == keyboard_input_listener )
		{
			return;
		}

		if( keyboard_input_listener != mKeyboardInputListener )
		{
			return;
		}

		mMachineInputCollector.RemoveObservationKeys( mKeyboardInputListener->GetObservationKeys() );

		mKeyboardInputListener = nullptr;
	}
}