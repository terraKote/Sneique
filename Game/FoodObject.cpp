#include <stdio.h>
#include "FoodObject.h"

const Vectormath::Vector2 FoodObject::GetPosition()
{
	return _position;
}

void FoodObject::MoveRandomly()
{
	bool isCellFree = false;
	int x = 0;
	int y = 0;
	_gridManager->GetRandomFreePosition(&x, &y);
	_position = { static_cast<float>(x * UNIT_SIZE), static_cast<float>(y * UNIT_SIZE) };

	printf("[Food] X: %i; Y: %i;\n", x, y);

	_spriteData->SetPosition(_position);
}
