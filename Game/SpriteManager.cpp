#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
	_createdSpritesCount = 0;
}

SpriteManager::~SpriteManager()
{
	for (auto spriteset : _loadedSpritesets)
	{
		TLN_DeleteSpriteset(spriteset.second);
	}

	_loadedSpritesets.clear();
}

void SpriteManager::LoadSpriteset(std::string path, std::string name)
{
	TLN_Spriteset spriteset = TLN_LoadSpriteset(path.c_str());
	_loadedSpritesets[name] = spriteset;
}

SpriteData SpriteManager::GetSpriteData()
{
	SpriteData spriteData(_createdSpritesCount);
	_createdSpritesCount++;
	return spriteData;
}

void SpriteManager::SetSpriteset(SpriteData* spriteData, std::string spritesetName)
{
	TLN_Spriteset spriteSet = _loadedSpritesets[spritesetName];
	TLN_SetSpriteSet(spriteData->GetIndex(), spriteSet);
}

void SpriteManager::SetSpritePosition(SpriteData* spriteData, int x, int y)
{
	TLN_SetSpritePosition(spriteData->GetIndex(), x, y);
}

void SpriteManager::SetSpriteDataImage(SpriteData* spriteData, unsigned int imageIndex)
{
	TLN_SetSpritePicture(spriteData->GetIndex(), imageIndex);
}
