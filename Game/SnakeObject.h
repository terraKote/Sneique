#pragma once
#include "ObjectManager.h"

class SnakeObject : public Object
{
public:
	SnakeObject(int id) : Object(id) {}

	void Update(double deltaTime) override;
	void Draw(double deltaTime) override;
};

