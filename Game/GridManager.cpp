#include "GridManager.h"

void GridManager::SetCellState(unsigned int index, bool isFree)
{
	// Prevent setting the cells that are out of the screen bounds
	if (index > _grid.size() || index < 0)
		return;

	if (isFree) {
		_grid.reset(index);
		return;
	}

	_grid.set(index);
}

void GridManager::SetCellState(int x, int y, bool isFree)
{
	unsigned int index = PositionToCellIndex(x, y);
	SetCellState(index, isFree);
}

bool GridManager::IsCellFree(unsigned int index) const
{
	return !_grid.test(index);
}

unsigned int GridManager::PositionToCellIndex(int x, int y)
{
	return y * _columnCount + x;
}

void GridManager::GetRandomFreePosition(int* x, int* y)
{
	bool isFree = false;
	int tempX = 0;
	int tempY = 0;

	while (!isFree)
	{
		tempX = std::rand() % _columnCount;
		tempY = std::rand() % _rowCount;

		unsigned int index = PositionToCellIndex(tempX, tempY);
		isFree = IsCellFree(index);
	}

	*x = tempX;
	*y = tempY;
}
