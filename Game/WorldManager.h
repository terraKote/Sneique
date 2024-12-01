#pragma once
#include <string>
#include <vector>

#include "Singleton.h"
#include "Tilengine.h"

class LevelData {
private:
	TLN_Tilemap _tilemap;

public:
	LevelData(TLN_Tilemap tilemap) : _tilemap(tilemap) {}
	unsigned int GetRowCount() const;
	unsigned int GetColumnCount() const;
	bool TileExists(int x, int y) const;
};

class WorldManager
{
	friend class Singleton<WorldManager>;
private:
	std::vector<LevelData> _levelData;
	WorldManager() = default;
	~WorldManager() = default;

public:
	void Load(std::string path, unsigned int layerIndex);
	LevelData GetLevelData(unsigned int layerIndex);
};

