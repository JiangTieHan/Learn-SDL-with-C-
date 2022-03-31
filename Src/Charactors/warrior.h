#pragma once

#include "character.h"
#include "../Animation/animation.h"
#include "../Physics/rigidBody.h"

class Warrior :public Character
{
public:
	Warrior(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

	virtual void Draw() override;
	virtual void Update(float dt) override;
	virtual void Clean() override;

private:

	Animation* m_Animation;
	RigidBody* m_RigidBody;
};
