#pragma once
#include <unordered_map>
#include <string>

#include <Tilengine.h>

#include "Singleton.h"

struct SpriteData {
private:
	unsigned int _index;

public:
	SpriteData(unsigned int index) : _index(index) {}

	unsigned int GetIndex()
	{
		return _index;
	}
};

class SpriteManager
{
	friend class Singleton<SpriteManager>;
private:
	unsigned int _createdSpritesCount;
	std::unordered_map<std::string, TLN_Spriteset> _loadedSpritesets;

	SpriteManager();
	~SpriteManager();

public:
	void LoadSpriteset(std::string path, std::string name);
	SpriteData GetSpriteData();
	void SetSpriteset(SpriteData* spriteData, std::string spritesetName);
	void SetSpritePosition(SpriteData* spriteData, int x, int y);
	void SetSpriteDataImage(SpriteData* spriteData, unsigned int imageIndex);
};

