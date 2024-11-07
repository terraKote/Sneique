#pragma once
#include <deque>
#include <vectormath.hpp>

#include "Constants.h"
#include "ObjectManager.h"

enum Direction {
	Up,
	Left,
	Down,
	Right
};

class SnakeObject : public Object
{
private:
	Direction _currentDirection;
	std::deque<Vectormath::Vector2> _snakeBody;
	Vectormath::Vector2 _velocity;
	double _moveTime;
	double _currentMoveTime;

public:
	SnakeObject(int id) : Object(id) {
		_currentDirection = Direction::Up;
		_snakeBody = { Vectormath::Vector2{0 * UNIT_SIZE,0}, Vectormath::Vector2{1 * UNIT_SIZE,0}, Vectormath::Vector2{2 * UNIT_SIZE,0} };
		_velocity = { 0, 0 };
		_moveTime = 0.15;
		_currentMoveTime = 0.0;
	}

	void Update(double deltaTime) override;
	void Draw(double deltaTime) override;
};

