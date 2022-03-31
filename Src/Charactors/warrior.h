#pragma once

#include "character.h"

class Warrior :public Character
{
public:
	Warrior(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

	virtual void Draw() override;
	virtual void Update(float dt) override;
	virtual void Clean() override;

private:
	int m_Row, m_Frame, m_FrameCount;
	int m_AnimationSpeed;
};
