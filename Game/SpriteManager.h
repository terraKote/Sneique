#pragma once
#include <unordered_map>
#include <string>

#include <vectormath.hpp>
#include <Tilengine.h>

#include "Constants.h"
#include "Singleton.h"

struct SpriteData {
private:
	unsigned int _index;
	Vectormath::Vector2 _position;
	unsigned int _spriteIndex;
	std::string _spriteset;
	bool _isReleased;

public:
	SpriteData() = default;
	SpriteData(unsigned int index) {
		_index = index;
		_position = { 0, 0 };
		_spriteIndex = 0;
		_spriteset = { 0 };
		_isReleased = true;
	}

	unsigned int GetIndex() const
	{
		return _index;
	}

	void SetPosition(Vectormath::Vector2 position) {
		_position = position;
	}

	Vectormath::Vector2 GetPosition() const {
		return _position;
	}

	void SetSpriteIndex(unsigned int index) {
		_spriteIndex = index;
	}

	unsigned int GetSpriteIndex() const {
		return _spriteIndex;
	}

	void SetSpriteSet(std::string name) {
		_spriteset = name;
	}

	std::string GetSpriteset() const {
		return _spriteset;
	}

	void Release() {
		_isReleased = true;
	}

	void Grab() {
		_isReleased = false;
	}

	bool IsReleased() const {
		return _isReleased;
	}
};

class SpriteManager
{
	friend class Singleton<SpriteManager>;
private:
	SpriteData _createdSprites[MAX_SPRITES];
	std::unordered_map<std::string, TLN_Spriteset> _loadedSpritesets;

	SpriteManager();
	~SpriteManager();

public:
	void LoadSpriteset(std::string path, std::string name);
	SpriteData* GetSpriteData();
	void UpdateSprites();
};

