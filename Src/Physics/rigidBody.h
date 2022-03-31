#pragma once

#include "vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody
{
public:
	RigidBody() 
	{
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}

	inline void SetMass(const float mass) { m_Mass = mass; }
	inline void SetGravity(const float gravity) { m_Gravity = gravity; }

	inline void ApplyForce(const Vector2D& force) { m_Force = force; }
	inline void ApplyForceX(const float forceX) { m_Force.X = forceX; }
	inline void ApplyForceY(const float forceY) { m_Force.Y = forceY; }
	inline void UnSetForce() { m_Force = Vector2D(0, 0); }

	inline void ApplyFriction(const Vector2D& friction) { m_Friction = friction; }
	inline void UnSetFriction() { m_Friction = Vector2D(0, 0); }

	inline float GetMass() const { return m_Mass; }
	inline Vector2D GetPosition() const { return m_Position; }
	inline Vector2D GetVelocity() const { return m_Velocity; }
	inline Vector2D GetAccelaration() const { return m_Accelaration; }

	// update method
	void Update(float dt)
	{
		m_Accelaration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Accelaration.Y = m_Gravity + m_Force.Y / m_Mass;
		m_Velocity = m_Accelaration * dt;
		m_Position = m_Velocity * dt;
	}


	//inline void SetPosition(const Vector2D& position) { m_Position = position; }
	//inline void SetVelocity(const Vector2D& velocity) { m_Velocity = velocity; }
	//inline void SetAccelaration(const Vector2D& accelaration) { m_Accelaration = accelaration; }


private:
	float m_Mass;
	float m_Gravity;

	Vector2D m_Force;
	Vector2D m_Friction;

	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_Accelaration;
};