#pragma once

#include "character.h"
#include "../Animation/animation.h"
#include "../Physics/rigidBody.h"
#include "../Collision/AABB.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

class Warrior :public Character
{
public:
	Warrior(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

	virtual void Draw() override;
	virtual void Update(float dt) override;
	virtual void Clean() override;

private:
	bool m_IsJumping;
	bool m_IsGrounded;

	float m_JumpTime;
	float m_JumpForce;
	AABB* m_Collider;

	Animation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;
};
