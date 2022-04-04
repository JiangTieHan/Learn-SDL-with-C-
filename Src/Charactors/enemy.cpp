#include "enemy.h"
#include "../Collision/collisionHandler.h"
#include "../Factory/objFactory.h"

static Registrar<Enemy> registrar("BOSS");

Enemy::Enemy(Properties* props) : Character(props)
{
	m_RigidBody = new RigidBody();
	if (m_RigidBody)
	{
		m_RigidBody->SetGravity(3.5f);
	}
	m_Collider = new AABB();
	m_Amimation = new SeqAnimation(false);
	if (m_Amimation)
	{
		m_Amimation->Parse("assets/animation.aml");
		m_Amimation->SetCurrentSeq("boss_appear");
	}
}

void Enemy::Draw()
{
	m_Amimation->DrawFrame(m_Transform->X, m_Transform->Y, 0.3f, 0.3f, m_Flip);
	
	// draw AABB
	if (false)
	{
		m_Collider->Draw();
	}
}

void Enemy::Clean()
{
	delete m_RigidBody;
	delete m_Collider;
	delete m_Amimation;
}

void Enemy::Update(float dt)
{
	// x movement
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 140, 100);

	if (m_Collider->CollidWithMap())
		m_Transform->X = m_LastSafePosition.X;

	// y movement
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 140, 100);

	if (m_Collider->CollidWithMap())
		m_Transform->Y = m_LastSafePosition.Y;

	m_Amimation->Update(dt);
	if (m_Amimation->GetIsEnded())
	{
		m_Amimation->SetRepeat(true);
		m_Amimation->SetCurrentSeq("boss_idle");
	}
}
