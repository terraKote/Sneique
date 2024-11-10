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

	InputManager()
	{
		_inputState = { 0 };
	}
	~InputManager() = default;

public:
	void SetButtonState(uint32_t button, uint8_t state);
	bool IsButtonPressed(uint32_t button);
};

