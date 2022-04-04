#pragma once

#include "character.h"
#include "../Animation/spriteAnimation.h"
#include "../Physics/rigidBody.h"
#include "../Collision/AABB.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f
#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Warrior :public Character
{
public:
	Warrior(Properties* props);

	virtual void Draw() override;
	virtual void Update(float dt) override;
	virtual void Clean() override;

private:
	void AnimationState();

private:
	bool m_IsJumping;
	bool m_IsGrounded;
	bool m_IsRunning;
	bool m_IsFalling;
	bool m_IsAttacking;
	bool m_IsCrouching;

	float m_JumpTime;
	float m_JumpForce;
	float m_AttackTime;

	AABB* m_Collider;
	SpriteAnimation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_LastSafePosition;
};
