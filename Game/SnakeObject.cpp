#include <iostream>
#include "SnakeObject.h"

void SnakeObject::Update(double deltaTime) {
	_currentMoveTime += deltaTime;

	if (_inputManager->IsButtonPressed(SNAKE_KEY_UP) && _currentDirection != Direction::Down) {
		_velocity.setX(0);
		_velocity.setY(-1);
		_currentDirection = Direction::Up;
		_currentMoveTime = _moveTime;
	}
	else if (_inputManager->IsButtonPressed(SNAKE_KEY_DOWN) && _currentDirection != Direction::Up) {
		_velocity.setX(0);
		_velocity.setY(1);
		_currentDirection = Direction::Down;
		_currentMoveTime = _moveTime;
	}
	else if (_inputManager->IsButtonPressed(SNAKE_KEY_LEFT) && _currentDirection != Direction::Right) {
		_velocity.setX(-1);
		_velocity.setY(0);
		_currentDirection = Direction::Left;
		_currentMoveTime = _moveTime;
	}
	else if (_inputManager->IsButtonPressed(SNAKE_KEY_RIGHT) && _currentDirection != Direction::Left) {
		_velocity.setX(1);
		_velocity.setY(0);
		_currentDirection = Direction::Right;
		_currentMoveTime = _moveTime;
	}

	bool addSegment = false;
	Vectormath::Vector2 head = _snakeBody[0];

	if (_currentMoveTime < _moveTime)
		return;

	// Check for collision with the food
	if (head.getX() == _foodObject->GetPosition().getX() && head.getY() == _foodObject->GetPosition().getY())
	{
		addSegment = true;
	}

	// Check collisiton with the world
	int headX = static_cast<int>(head.getX());
	int headY = static_cast<int>(head.getY());
	LevelData levelData = _worldManager->GetLevelData(0);

	if (levelData.TileExists(headX / UNIT_SIZE, headY / UNIT_SIZE))
	{
		Reset();
		return;
	}

	// Check for collision with itself
	for (unsigned int i = 0; i < _snakeBody.size(); i++) {
		// Skip the head
		if (i == 0)
			continue;

		Vectormath::Vector2 bodySegment = _snakeBody[i];

		if (head.getX() == bodySegment.getX() && head.getY() == bodySegment.getY()) {
			Reset();
			return;
		}
	}

	// Set cells free
	for (unsigned int i = 0; i < _snakeBody.size(); i++) {
		Vectormath::Vector2 segment = _snakeBody[i];
		int x = static_cast<int>(segment.getX() / UNIT_SIZE);
		int y = static_cast<int>(segment.getY() / UNIT_SIZE);
		_gridManager->SetCellState(x, y, true);
	}

	// Handle the snake movement
	if (Vectormath::length(_velocity) > 0.0f)
	{
		Vectormath::Vector2 headPosition = { head.getX() + _velocity.getX() * UNIT_SIZE, head.getY() + _velocity.getY() * UNIT_SIZE };
		_snakeBody.push_front(headPosition);

		if (addSegment) {
			SpriteData* sprite = _spriteManager->GetSpriteData();
			_sprites.push_back(sprite);
			sprite->SetSpriteSet("snake");
		}
		else {
			_snakeBody.pop_back();
		}
	}

	// Set cells taken
	for (unsigned int i = 0; i < _snakeBody.size(); i++) {
		Vectormath::Vector2 segment = _snakeBody[i];
		int x = static_cast<int>(segment.getX() / UNIT_SIZE);
		int y = static_cast<int>(segment.getY() / UNIT_SIZE);
		_gridManager->SetCellState(x, y, false);
	}

	// Move the food
	if (addSegment) {
		_foodObject->MoveRandomly();
	}

	// Draw the snake
	for (unsigned int i = 0; i < _snakeBody.size(); i++) {
		Vectormath::Vector2 point = _snakeBody[i];
		unsigned int spriteIndex = static_cast<unsigned int>(_currentDirection);

		if (i != 0)
		{
			spriteIndex = 4;
		}

		_sprites[i]->SetSpriteIndex(spriteIndex);
		_sprites[i]->SetPosition(point);
	}

	_currentMoveTime = 0;
}

void SnakeObject::Reset() {
	_currentMoveTime = 0;
	float y = 3 * UNIT_SIZE;
	_snakeBody = { Vectormath::Vector2{4 * UNIT_SIZE,y}, Vectormath::Vector2{5 * UNIT_SIZE,y}, Vectormath::Vector2{6 * UNIT_SIZE,y} };
	_currentDirection = Direction::Left;
	_velocity = { 0, 0 };

	for (unsigned int i = _sprites.size() - 1; i > _snakeBody.size() - 1; i--)
	{
		_sprites[i]->Release();
		_sprites.pop_back();
	}
}