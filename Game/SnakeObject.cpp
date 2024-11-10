#include <iostream>
#include "SnakeObject.h"

void SnakeObject::Update(double deltaTime) {
	if (_inputManager->IsButtonPressed(SNAKE_KEY_UP)) {
		_velocity.setX(0);
		_velocity.setY(-1);
		_currentDirection = Direction::Up;
	}
	else if (_inputManager->IsButtonPressed(SNAKE_KEY_DOWN)) {
		_velocity.setX(0);
		_velocity.setY(1);
		_currentDirection = Direction::Down;
	}
	else if (_inputManager->IsButtonPressed(SNAKE_KEY_LEFT)) {
		_velocity.setX(-1);
		_velocity.setY(0);
		_currentDirection = Direction::Left;
	}
	else if (_inputManager->IsButtonPressed(SNAKE_KEY_RIGHT)) {
		_velocity.setX(1);
		_velocity.setY(0);
		_currentDirection = Direction::Right;
	}

	bool addSegment = false;

	if (_snakeBody[0].getX() == _foodObject->GetPosition().getX() && _snakeBody[0].getY() == _foodObject->GetPosition().getY())
	{
		addSegment = true;

		//fruitPosition = GetRandomPosition();
	}

	_currentMoveTime += deltaTime;

	if (_currentMoveTime < _moveTime)
		return;

	if (addSegment)
	{
		Vectormath::Vector2 headPosition = { _snakeBody[0].getX() + _velocity.getX() * UNIT_SIZE, _snakeBody[0].getY() + _velocity.getY() * UNIT_SIZE };
		_snakeBody.push_front(headPosition);

		SpriteData sprite = _spriteManager->GetSpriteData();
		_spriteManager->SetSpriteset(&sprite, "snake");
		_sprites.push_back(sprite);

		_foodObject->MoveRandomly();
	}
	else {
		_snakeBody.pop_back();
		Vectormath::Vector2 headPosition = { _snakeBody[0].getX() + _velocity.getX() * UNIT_SIZE, _snakeBody[0].getY() + _velocity.getY() * UNIT_SIZE };
		_snakeBody.push_front(headPosition);
	}

	_currentMoveTime = 0;
}

void SnakeObject::Draw(double deltaTime) {
	for (unsigned int i = 0; i < _snakeBody.size(); i++) {
		Vectormath::Vector2 point = _snakeBody[i];
		int spriteIndex = static_cast<int>(_currentDirection);

		if (i != 0)
		{
			spriteIndex = 4;
		}

		_spriteManager->SetSpriteDataImage(&_sprites[i], spriteIndex);
		_spriteManager->SetSpritePosition(&_sprites[i], point.getX(), point.getY());
	}
}