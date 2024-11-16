#include "FoodObject.h"

const Vectormath::Vector2 FoodObject::GetPosition()
{
	return _position;
}

void FoodObject::MoveRandomly()
{
	int cellCountHorizontal = RENDER_WIDTH / UNIT_SIZE;
	int cellCountVertical = RENDER_HEIGHT / UNIT_SIZE;

	bool isCellFree = false;

	while (!isCellFree)
	{
		_position = { static_cast<float>(std::rand() % cellCountHorizontal * UNIT_SIZE), static_cast<float>(std::rand() % cellCountVertical * UNIT_SIZE) };
		unsigned int index = (_position.getX() / UNIT_SIZE) * (_position.getY() / UNIT_SIZE);
		isCellFree = _gridManager->IsCellFree(index);
	}

	_spriteData->SetPosition(_position);
}
