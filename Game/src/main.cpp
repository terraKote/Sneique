#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "Constants.h"
#include "ObjectManager.h"
#include "SpriteManager.h"
#include "SnakeObject.h"
#include "InputManager.h"
#include "FoodObject.h"
#include "GridManager.h"

#define APP_NAME "Sneique"

int main(int argc, char* argv[]) {

	// Window setup
	const int width = 640;
	const int height = 480;
	const int targetFps = 60;

	InitWindow(width, height, APP_NAME);
	SetTargetFPS(targetFps);

	// Camera setup
	Camera2D worldCamera = { 0 };
	worldCamera.zoom = 1;

	// Virtual texture setup
	const int virtualWidth = 320;
	const int virtualHeight = 240;
	const float virtualRatio = static_cast<float>(virtualWidth) / static_cast<float>(virtualHeight);

	RenderTexture2D renderTexture = LoadRenderTexture(virtualWidth, virtualHeight);

	Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(renderTexture.texture.width), -static_cast<float>(renderTexture.texture.height) };
	Rectangle destRec = { -virtualRatio, -virtualRatio, width + (virtualRatio * 2), height + (virtualRatio * 2) };

	// Sprite setup
	Texture2D snakeSpritesheet = LoadTexture("assets/sprites/snake.png");
	Rectangle srcRect = Rectangle{ 40, 24, 8, 8 };
	Rectangle dstRect = Rectangle{ 0,0,8,8 };

	while (!WindowShouldClose()) {
		// Render to virtual texture
		BeginTextureMode(renderTexture);
		ClearBackground(RAYWHITE);
		BeginMode2D(worldCamera);
		DrawTexturePro(snakeSpritesheet, srcRect, dstRect, { 0, 0 }, 0, WHITE);
		EndMode2D();
		EndTextureMode();

		// Render to the screen
		BeginDrawing();
		ClearBackground(RED);
		DrawTexturePro(renderTexture.texture, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
		EndDrawing();
	}

	// Unload textures
	UnloadTexture(snakeSpritesheet);
	UnloadRenderTexture(renderTexture);

	// Close the app
	CloseWindow();
	return 0;
}