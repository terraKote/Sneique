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

bool GridManager::IsCellFree(unsigned int index) const
{
	return !_grid.test(index);
}
