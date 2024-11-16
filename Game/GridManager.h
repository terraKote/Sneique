#pragma once
#include <bitset>

#include "Constants.h"
#include "ObjectManager.h"

class GridManager : public Object
{
private:
	std::bitset<GRID_SIZE> _grid;

public:
	GridManager(int id, std::string name) : Object(id, name) {
		_grid = 0;
	}

	void SetCellState(unsigned int index, bool isFree);
	bool IsCellFree(unsigned int index) const;
};

