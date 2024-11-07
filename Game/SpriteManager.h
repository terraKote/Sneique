#pragma once
#include <unordered_map>
#include <string>

#include <Tilengine.h>

struct SpriteData {
private:
	unsigned int _index;

public:
	SpriteData(unsigned int index) : _index(index){}

	unsigned int GetIndex()
	{
		return _index;
	}
};

class SpriteManager
{
private:
	unsigned int _createdSpritesCount;
	std::unordered_map<std::string, TLN_Spriteset> _loadedSpritesets;

public:
	SpriteData GetSpriteData();
	void SetSpriteset(SpriteData* spriteData, std::string spritesetName);
	void SetSpritePosition(SpriteData* spriteData, int x, int y);
	void SetSpriteDataImage(SpriteData* spriteData, unsigned int imageIndex);
};

