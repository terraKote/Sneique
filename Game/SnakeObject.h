#pragma once
#include <deque>
#include <string>
#include <vector>
#include <vectormath.hpp>

#include "Constants.h"
#include "Singleton.h"
#include "ObjectManager.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "FoodObject.h"

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
	std::vector<SpriteData> _sprites;
	Vectormath::Vector2 _velocity;
	double _moveTime;
	double _currentMoveTime;
	SpriteManager* _spriteManager;
	InputManager* _inputManager;
	ObjectManager* _objectManager;
	FoodObject* _foodObject;

public:
	SnakeObject(int id, std::string name) : Object(id, name) {
		_currentDirection = Direction::Up;
		_snakeBody = { Vectormath::Vector2{0 * UNIT_SIZE,0}, Vectormath::Vector2{1 * UNIT_SIZE,0}, Vectormath::Vector2{2 * UNIT_SIZE,0} };
		_velocity = { 0, 0 };
		_moveTime = 0.15;
		_currentMoveTime = 0.0;
		_spriteManager = Singleton<SpriteManager>::GetInstance();
		_inputManager = Singleton<InputManager>::GetInstance();
		_objectManager = Singleton<ObjectManager>::GetInstance();

		for (const auto bodyBlock : _snakeBody)
		{
			SpriteData sprite = _spriteManager->GetSpriteData();
			_sprites.push_back(sprite);
			_spriteManager->SetSpriteset(&sprite, "snake");
		}

		_foodObject = static_cast<FoodObject*>(_objectManager->FindObject("food"));
	}

	void Update(double deltaTime) override;
	void Draw(double deltaTime) override;
};

