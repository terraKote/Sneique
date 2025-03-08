#include "raylib.h"
#include <vector>

struct Snake {
	std::vector<Vector2> body;
	Vector2 direction;
};

void UpdateSnake(Snake& snake) {
	// Move the snake
	for (int i = snake.body.size() - 1; i > 0; --i) {
		snake.body[i] = snake.body[i - 1];
	}
	snake.body[0].x += snake.direction.x;
	snake.body[0].y += snake.direction.y;
}

void DrawGame(const Snake& snake, const Vector2& food) {
	const int cellSize = 40;

	// Draw food
	DrawRectangle(food.x * cellSize, food.y * cellSize, cellSize, cellSize, RED);

	// Draw snake
	for (const auto& segment : snake.body) {
		DrawRectangle(segment.x * cellSize, segment.y * cellSize, cellSize, cellSize, GREEN);
	}
}

bool CheckCollision(const Snake& snake) {
	// Check wall collision
	if (snake.body[0].x < 0 || snake.body[0].x >= 20 ||
		snake.body[0].y < 0 || snake.body[0].y >= 20) {
		return true;
	}

	// Check self-collision
	for (size_t i = 1; i < snake.body.size(); ++i) {
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
			return true;
		}
	}

	return false;
}

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;
	const int cellSize = 40;

	InitWindow(screenWidth, screenHeight, "Snake Game");
	SetTargetFPS(60);

	Snake snake = { {{5, 5}}, {1, 0} };
	Vector2 food = { GetRandomValue(0, 19), GetRandomValue(0, 19) };

	float moveInterval = 0.2f; // Time between snake movements (in seconds)
	float moveTimer = 0.0f;    // Timer to track elapsed time

	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime(); // Get time since last frame

		// Input handling
		if (IsKeyPressed(KEY_RIGHT)) snake.direction = { 1, 0 };
		if (IsKeyPressed(KEY_LEFT)) snake.direction = { -1, 0 };
		if (IsKeyPressed(KEY_UP)) snake.direction = { 0, -1 };
		if (IsKeyPressed(KEY_DOWN)) snake.direction = { 0, 1 };

		// Update snake movement timer
		moveTimer += deltaTime;
		if (moveTimer >= moveInterval) {
			moveTimer = 0.0f; // Reset timer
			// Update snake
			UpdateSnake(snake);
		}

		// Check for food collision
		if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
			snake.body.push_back(snake.body.back());
			food = { static_cast<float>(GetRandomValue(0, 10)), static_cast<float>(GetRandomValue(0, 10)) };
		}

		//// Check for game over
		//if (CheckCollision(snake)) {
		//	break; // End game
		//}

		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawGame(snake, food);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}