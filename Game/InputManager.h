#pragma once
#include <cstdint>
#include <SDL.h>
#include "Singleton.h"

#define SNAKE_KEY_UP SDLK_UP
#define SNAKE_KEY_DOWN SDLK_DOWN
#define SNAKE_KEY_LEFT SDLK_LEFT
#define SNAKE_KEY_RIGHT SDLK_RIGHT
#define SNAKE_KEY_ACTION SDLK_z

class InputManager
{
	friend class Singleton<InputManager>;
private:
	uint32_t _inputState;
	uint32_t _previousInputState;

	InputManager()
	{
		_inputState = { 0 };
		_previousInputState = { 0 };
	}
	~InputManager() = default;

	void SetBufferState(uint32_t* buffer, uint32_t button, bool state);

public:
	void SetButtonState(uint32_t button, bool state);
	bool IsButtonPressed(uint32_t button);
};

