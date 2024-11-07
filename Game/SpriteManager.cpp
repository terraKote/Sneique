#include "SpriteManager.h"

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
