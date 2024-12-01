#pragma once
#include <bitset>

#include "Constants.h"
#include "ObjectManager.h"
#include "WorldManager.h"

class GridManager : public Object
{
private:
	std::bitset<MAX_WORLD_SIZE> _grid;
	unsigned int _rowCount;
	unsigned int _columnCount;

public:
	GridManager(int id, std::string name) : Object(id, name) {
		_grid = 0;

		WorldManager* worldManager = Singleton<WorldManager>::GetInstance();
		LevelData levelData = worldManager->GetLevelData(0);

		_rowCount = levelData.GetRowCount();
		_columnCount = levelData.GetColumnCount();

		for (int row = 0; row < _rowCount; row++)
		{
			for (int column = 0; column < _columnCount; column++)
			{
				bool tileExists = levelData.TileExists(row, column);
				unsigned int index = PositionToCellIndex(column, row);
				SetCellState(index, !tileExists);
				printf("Tile X: %i; Y: %i; Taken: %i; Index: %i;\n", column, row, tileExists, index);
			}
		}
	}

	void SetCellState(unsigned int index, bool isFree);
	void SetCellState(int x, int y, bool isFree);
	bool IsCellFree(unsigned int index) const;
	unsigned int PositionToCellIndex(int x, int y);
	void GetRandomFreePosition(int* x, int* y);
};

