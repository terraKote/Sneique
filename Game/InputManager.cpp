#include "InputManager.h"

void InputManager::SetButtonState(uint32_t button, uint8_t state)
{
	switch (state)
	{
	default:
	case 0:
		_inputState &= ~(1 << button);
		break;

	case 1:
		_inputState |= (1 << button);
		break;
	}
}

bool InputManager::IsButtonPressed(uint32_t button)
{
	int state = _inputState & 1 << button;
	return state != 0;
}
