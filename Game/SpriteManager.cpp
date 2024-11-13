#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
	for (unsigned int i = 0; i < MAX_SPRITES; i++) {
		SpriteData spriteData(i);
		_createdSprites[i] = spriteData;
	}
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

SpriteData* SpriteManager::GetSpriteData()
{
	//
	TLN_GetAvailableSprite();

	for (unsigned int i = 0; i < MAX_SPRITES; i++) {
		if (!_createdSprites[i].IsReleased())
			continue;

		_createdSprites[i].Grab();
		return &_createdSprites[i];
	}
}

void SpriteManager::UpdateSprites()
{
	for (unsigned int i = 0; i < MAX_SPRITES; i++) {
		SpriteData spriteData = _createdSprites[i];

		if (spriteData.IsReleased())
		{
			TLN_DisableSprite(spriteData.GetIndex());
			continue;
		}

		// Set spriteset
		TLN_Spriteset spriteSet = _loadedSpritesets[spriteData.GetSpriteset()];
		TLN_SetSpriteSet(spriteData.GetIndex(), spriteSet);

		// Set sprite position
		Vectormath::Vector2 position = spriteData.GetPosition();
		TLN_SetSpritePosition(spriteData.GetIndex(), position.getX(), position.getY());

		// Set sprite index
		TLN_SetSpritePicture(spriteData.GetIndex(), spriteData.GetSpriteIndex());
	}
}
