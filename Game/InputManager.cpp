#include "InputManager.h"

void InputManager::SetBufferState(uint32_t* buffer, uint32_t button, bool state)
{
	if (state) {
		*buffer |= (1 << button);
		return;
	}

	*buffer &= ~(1 << button);
}

void InputManager::SetButtonState(uint32_t button, bool state)
{
	SetBufferState(&_inputState, button, state);
}

bool InputManager::IsButtonPressed(uint32_t button)
{
	bool currentState = _inputState & 1 << button;
	bool previousState = _previousInputState & 1 << button;

	if (currentState != previousState)
	{
		SetBufferState(&_previousInputState, button, !previousState);
	}

	return currentState && currentState != previousState;
}
