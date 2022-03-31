#pragma once

#include "../Object/gameObject.h"
#include <string>

class Character : public GameObject
{
public:
	Character(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) :
		GameObject(TextureID, x, y, width, height, flip){}

	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

protected:
	std::string m_Name;
};
