#pragma once
#include <cstdint>
#include "Singleton.h"

class InputManager
{
	friend class Singleton<InputManager>;
private:
	uint32_t _inputState;

	InputManager() = default;
	~InputManager() = default;

public:
	void SetButtonState(uint32_t button, uint8_t state);
	bool IsButtonPressed(uint32_t button);
};

