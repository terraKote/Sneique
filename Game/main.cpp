#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <Tilengine.h>
#include <vectormath.hpp>

#include "Constants.h"
#include "ObjectManager.h"
#include "SpriteManager.h"
#include "SnakeObject.h"
#include "InputManager.h"
#include "FoodObject.h"
#include "GridManager.h"

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

Vectormath::Vector2 GetRandomPosition();

int main(int argc, char* argv[]) {
	uint8_t* rt_pixels = { 0 };
	int rt_pitch = { 0 };
	bool quit = false;
	int millisecondsPassed = 0;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Detect the suitable screen resolution
	SDL_DisplayMode displayMode = { 0 };

	if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
	{
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		return 1;
	}

	SDL_Rect dstrect = { 0 };
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = displayMode.w;
	dstrect.h = displayMode.h;

	// Create a window
	SDL_Window* window = SDL_CreateWindow("Sneique",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		displayMode.w, displayMode.h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

	if (window == nullptr) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED + SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* backbuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);

	TLN_Init(RENDER_WIDTH, RENDER_HEIGHT, 2, MAX_SPRITES, 0);

	TLN_Spriteset spriteset = TLN_LoadSpriteset("assets/sprites/snake");

	ObjectManager* objectManager = Singleton<ObjectManager>::GetInstance();
	SpriteManager* spriteManager = Singleton<SpriteManager>::GetInstance();
	InputManager* inputManager = Singleton<InputManager>::GetInstance();

	spriteManager->LoadSpriteset("assets/sprites/snake", "snake");

	GridManager* gridManager = objectManager->CreateObject<GridManager>("gridManager");
	FoodObject* foodObject = objectManager->CreateObject<FoodObject>("food");
	SnakeObject* snakeObject = objectManager->CreateObject<SnakeObject>("snake");

	TLN_SetBGColor(255, 255, 255);

	// Main application loop
	while (!quit) {
		// Event processing
		SDL_Event evt;
		SDL_KeyboardEvent* keybevt;

		while (SDL_PollEvent(&evt) != 0) {
			switch (evt.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				keybevt = (SDL_KeyboardEvent*)&evt;
				inputManager->SetButtonState(static_cast<uint32_t>(keybevt->keysym.sym), true);
				break;

			case SDL_KEYUP:
				keybevt = (SDL_KeyboardEvent*)&evt;
				inputManager->SetButtonState(static_cast<uint32_t>(keybevt->keysym.sym), false);
				break;
			}
		}

		// Game loop limit
		uint32_t currentTicks = SDL_GetTicks();
		int ticksToWait = MILLISECONDS_PER_FRAME - (currentTicks - millisecondsPassed);

		if (ticksToWait > 0 && ticksToWait <= MILLISECONDS_PER_FRAME)
		{
			SDL_Delay(ticksToWait);
		}

		double deltaTime = (currentTicks - millisecondsPassed) / 1000.0;
		millisecondsPassed = currentTicks;

		// Game logic
		for (auto& element : objectManager->GetCreatedObjects())
		{
			element->Update(deltaTime);
		}

		spriteManager->UpdateSprites();

		// Render
		SDL_LockTexture(backbuffer, NULL, (void**)&rt_pixels, &rt_pitch);

		// Tilengine Draw Begin
		TLN_SetRenderTarget(rt_pixels, rt_pitch);

		TLN_UpdateFrame(0);
		// Tilengine Draw End

		SDL_UnlockTexture(backbuffer);
		SDL_RenderClear(renderer);
		SDL_SetTextureBlendMode(backbuffer, SDL_BLENDMODE_NONE);
		SDL_RenderCopy(renderer, backbuffer, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

	TLN_DeleteSpriteset(spriteset);

	TLN_Deinit();

	// Destroy the window and quit SDL
	SDL_DestroyTexture(backbuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

Vectormath::Vector2 GetRandomPosition() {
	int cellCountHorizontal = RENDER_WIDTH / UNIT_SIZE;
	int cellCountVertical = RENDER_HEIGHT / UNIT_SIZE;

	return { static_cast<float>(std::rand() % cellCountHorizontal * UNIT_SIZE), static_cast<float>(std::rand() % cellCountVertical * UNIT_SIZE) };
}