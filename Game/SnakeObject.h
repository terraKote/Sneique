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
#include "GridManager.h"

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
	std::vector<SpriteData*> _sprites;
	Vectormath::Vector2 _velocity;
	double _moveTime;
	double _currentMoveTime;
	SpriteManager* _spriteManager;
	InputManager* _inputManager;
	ObjectManager* _objectManager;
	FoodObject* _foodObject;
	GridManager* _gridManager;
	WorldManager* _worldManager;

public:
	SnakeObject(int id, std::string name) : Object(id, name) {
		_currentDirection = Direction::Left;
		_snakeBody = { Vectormath::Vector2{4 * UNIT_SIZE,3 * UNIT_SIZE}, Vectormath::Vector2{5 * UNIT_SIZE,3 * UNIT_SIZE}, Vectormath::Vector2{6 * UNIT_SIZE,3 * UNIT_SIZE} };
		_velocity = { 0, 0 };
		_moveTime = 0.15;
		_currentMoveTime = 0.0;
		_spriteManager = Singleton<SpriteManager>::GetInstance();
		_inputManager = Singleton<InputManager>::GetInstance();
		_objectManager = Singleton<ObjectManager>::GetInstance();
		_worldManager = Singleton<WorldManager>::GetInstance();

		for (const auto bodyBlock : _snakeBody)
		{
			SpriteData* sprite = _spriteManager->GetSpriteData();
			_sprites.push_back(sprite);
			sprite->SetSpriteSet("snake");
		}

		_foodObject = static_cast<FoodObject*>(_objectManager->FindObject("food"));
		_gridManager = static_cast<GridManager*>(_objectManager->FindObject("gridManager"));
	}

	void Update(double deltaTime) override;
	void Reset();
};

