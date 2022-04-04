#pragma once

#include "character.h"
#include "../Physics/rigidBody.h"
#include "../Collision/AABB.h"
#include "../Animation/seqAnimation.h"
#include "../Animation/spriteAnimation.h"

class Enemy : public Character
{
public:
	Enemy(Properties* props);

	virtual void Draw() override;
	virtual void Clean() override;
	virtual void Update(float dt) override;

private:
	AABB* m_Collider;
	RigidBody* m_RigidBody;
	SeqAnimation* m_Amimation;
	Vector2D m_LastSafePosition;
};

