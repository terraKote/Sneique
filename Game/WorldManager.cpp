#include "WorldManager.h"

unsigned int LevelData::GetRowCount() const
{
	return TLN_GetTilemapRows(_tilemap);
}

unsigned int LevelData::GetColumnCount() const
{
	return TLN_GetTilemapCols(_tilemap);
}

bool LevelData::TileExists(int x, int y) const
{
	TLN_Tile tile = TLN_GetTilemapTiles(_tilemap, x, y);
	return tile->value != 0;
}

void WorldManager::Load(std::string path, unsigned int layerIndex)
{
	TLN_LoadWorld(path.c_str(), layerIndex);
}

LevelData WorldManager::GetLevelData(unsigned int layerIndex)
{
	if (_levelData.size() == 0)
	{
		TLN_Tilemap map = TLN_GetLayerTilemap(layerIndex);
		LevelData levelData(map);
		_levelData.push_back(levelData);
	}

	LevelData levelData = _levelData.at(layerIndex);
	return levelData;
}
