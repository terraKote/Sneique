#pragma once
#include <cstdint>
#include <SDL.h>
#include "Singleton.h"

#define UP SDLK_UP
#define DOWN SDLK_DOWN
#define LEFT SDLK_LEFT
#define RIGHT SDLK_RIGHT
#define ACTION SDLK_z

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

