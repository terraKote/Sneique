#include <iostream>
#include "SnakeObject.h"

void SnakeObject::Update(double deltaTime) {
	if (_inputManager->IsButtonPressed(UP)) {
		_velocity.setX(0);
		_velocity.setY(-1);
		_currentDirection = Direction::Up;
	}
	else if (_inputManager->IsButtonPressed(DOWN)) {
		_velocity.setX(0);
		_velocity.setY(1);
		_currentDirection = Direction::Down;
	}
	else if (_inputManager->IsButtonPressed(LEFT)) {
		_velocity.setX(-1);
		_velocity.setY(0);
		_currentDirection = Direction::Left;
	}
	else if (_inputManager->IsButtonPressed(RIGHT)) {
		_velocity.setX(1);
		_velocity.setY(0);
		_currentDirection = Direction::Right;
	}

	bool addSegment = false;

	if (_inputManager->IsButtonPressed(ACTION)) {
		addSegment = true;
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
	}
	else {
		_snakeBody.pop_back();
		Vectormath::Vector2 headPosition = { _snakeBody[0].getX() + _velocity.getX() * UNIT_SIZE, _snakeBody[0].getY() + _velocity.getY() * UNIT_SIZE };
		_snakeBody.push_front(headPosition);
	}

	_currentMoveTime = 0;

	//	if (snakeBody[0].getX() == fruitPosition.getX() && snakeBody[0].getY() == fruitPosition.getY())
	//	{
	//		/*	Vectormath::Vector2 headPosition = { snakeBody[0].getX() + velocity.getX() * UNIT_SIZE, snakeBody[0].getY() + velocity.getY() * UNIT_SIZE };
	//			snakeBody.push_front(headPosition);*/

	//		fruitPosition = GetRandomPosition();
	//	}
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