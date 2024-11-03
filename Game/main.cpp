#include <iostream>
#include <deque>
#include <SDL.h>
#include <Tilengine.h>
#include <vectormath.hpp>

#define WIDTH 640
#define HEIGHT 480

#define RENDER_WIDTH 160
#define RENDER_HEIGHT 120

#define UNIT_SIZE 8

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

enum Direction {
	Up,
	Left,
	Down,
	Right
};

int main(int argc, char* argv[]) {
	SDL_Rect dstrect = { 0 };
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = WIDTH;
	dstrect.h = HEIGHT;

	std::deque<Vectormath::Vector2> snakeBody = { Vectormath::Vector2{0,0}, Vectormath::Vector2{1,0}, Vectormath::Vector2{2,0} };
	Vectormath::Vector2 velocity = { 0, 0 };

	uint8_t* rt_pixels = { 0 };
	int rt_pitch = { 0 };
	Direction currentDirection = Direction::Up;
	int millisecondsPassed = 0;

	double moveTime = 0.3;
	double currentMoveTime = 0.0;

	TLN_Spriteset spriteset;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create a window
	SDL_Window* window = SDL_CreateWindow("Snake Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED + SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* backbuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);

	// Main loop flag
	bool quit = false;
	SDL_Event evt;

	TLN_Init(RENDER_WIDTH, RENDER_HEIGHT, 2, 64, 0);
	TLN_SetLoadPath("assets/sprites");

	spriteset = TLN_LoadSpriteset("snake");
	TLN_SetSpriteSet(0, spriteset);
	TLN_SetSpriteSet(1, spriteset);
	TLN_SetSpriteSet(2, spriteset);

	TLN_SetBGColor(0, 0, 0);

	// Main application loop
	while (!quit) {
		// Event processing
		while (SDL_PollEvent(&evt) != 0) {
			switch (evt.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				SDL_KeyboardEvent* keybevt = (SDL_KeyboardEvent*)&evt;
				switch (keybevt->keysym.sym)
				{
				case SDLK_UP:
					currentDirection = Direction::Up;
					break;

				case SDLK_LEFT:
					currentDirection = Direction::Left;
					break;

				case SDLK_DOWN:
					currentDirection = Direction::Down;
					break;

				case SDLK_RIGHT:
					currentDirection = Direction::Right;
					break;
				}
				break;
			}
		}

		// Game loop limit
		int ticksToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsPassed);

		if (ticksToWait > 0 && ticksToWait <= MILLISECONDS_PER_FRAME)
		{
			SDL_Delay(ticksToWait);
		}

		double deltaTime = (SDL_GetTicks() - millisecondsPassed) / 1000.0;

		millisecondsPassed = SDL_GetTicks();

		// Game logic
		currentMoveTime += deltaTime;

		if (currentMoveTime >= moveTime) {
			switch (currentDirection)
			{
			case Up:
				velocity.setX(0);
				velocity.setY(-1);
				break;
			case Left:
				velocity.setX(-1);
				velocity.setY(0);
				break;
			case Down:
				velocity.setX(0);
				velocity.setY(1);
				break;
			case Right:
				velocity.setX(1);
				velocity.setY(0);
				break;
			}

			snakeBody.pop_back();
			Vectormath::Vector2 headPosition = { snakeBody[0].getX() + velocity.getX(), snakeBody[0].getY() + velocity.getY() };
			snakeBody.push_front(headPosition);

			currentMoveTime = 0;
		}

		for (unsigned int i = 0; i < snakeBody.size(); i++) {
			Vectormath::Vector2 point = snakeBody[i];

			int spriteIndex = currentDirection;

			if (i != 0)
			{
				spriteIndex = 4;
			}

			TLN_SetSpritePicture(i, spriteIndex);
			TLN_SetSpritePosition(i, point.getX() * UNIT_SIZE, point.getY() * UNIT_SIZE);
		}

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
