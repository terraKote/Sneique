#include "GridManager.h"

void GridManager::SetCellState(unsigned int index, bool isFree)
{
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
