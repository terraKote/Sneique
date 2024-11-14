#pragma once
#include <vectormath.hpp>

#include "Constants.h"
#include "ObjectManager.h"
#include "SpriteManager.h"

class FoodObject : public Object
{
private:
	SpriteManager* _spriteManager;
	SpriteData* _spriteData;
	Vectormath::Vector2 _position;

public:
	FoodObject(int id, std::string name) : Object(id, name)
	{
		_spriteManager = Singleton<SpriteManager>::GetInstance();
		_spriteData = _spriteManager->GetSpriteData();
		_position = { 6 * UNIT_SIZE, 6 * UNIT_SIZE };

		_spriteData->SetSpriteSet("snake");
		_spriteData->SetSpriteIndex(5);
		_spriteData->SetPosition(_position);
	}

	const Vectormath::Vector2 GetPosition();
	void MoveRandomly();
};

