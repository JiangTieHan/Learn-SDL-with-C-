#include "warrior.h"
#include "../Graphic/textureManager.h"
#include "../Inputs/input.h"
#include "../Camera/camera.h"
#include "../Core/engine.h"
#include "../Collision/collisionHandler.h"
#include <SDL.h>

Warrior::Warrior(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip)
	:Character(TextureID,x,y,width,height,flip),
	m_IsAttacking(false), m_IsCrouching(false), m_IsFalling(false), m_IsGrounded(false), m_IsJumping(false), m_IsRunning(false)
{
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;

	m_Collider = new AABB();
	m_Collider->SetBuffer(-60, -20, 0, 0);

	m_Animation = new SpriteAnimation();
	if (m_Animation)
	{
		m_Animation->SetProps(TextureID, 0, 6, 150);
	}

	m_RigidBody = new RigidBody();
	if (m_RigidBody)
	{
		m_RigidBody->SetGravity(3.0f);
	}
}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

	// draw collider box
	if (false)
	{
		Vector2D cam = Camera::GetInstance(SCREEN_WIDTH, SCREEN_HIGHT)->GetPosition();
		SDL_Rect box = m_Collider->Get();
		box.x -= cam.X;
		box.y -= cam.Y;
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
	}
}

void Warrior::Update(float dt)
{
	m_IsRunning = false;
	m_IsCrouching = false;
	m_RigidBody->UnSetForce();

	// run forward
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking)
	{
		m_RigidBody->ApplyForceX(RUN_FORCE * FORWARD);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
	}

	// run backward
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking)
	{
		m_RigidBody->ApplyForceX(RUN_FORCE * BACKWARD);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsRunning = true;
	}

	// crouch
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
	{
		m_RigidBody->UnSetForce();
		m_IsCrouching = true;
	}

	// attack
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K))
	{
		m_RigidBody->UnSetForce();
		m_IsAttacking = true;
	}

	// jump
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
	{
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0)
	{
		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
	}
	else
	{
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

	// fall
	if (m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded)
		m_IsFalling = true;
	else
		m_IsFalling = false;

	// attack timer
	if (m_IsAttacking && m_AttackTime > 0)
	{
		m_AttackTime -= dt;
	}
	else
	{
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}

	// move on X
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
		m_Transform->X = m_LastSafePosition.X;

	// move on Y
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
	{
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else
	{
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	AnimationState();

	m_Animation->Update(dt);
}

void Warrior::Clean()
{
	delete m_Animation;
	delete m_RigidBody;
	delete m_Collider;
	TextureManager::GetInstance()->Drop(m_TextureID);
}

void Warrior::AnimationState()
{
	// idle
	m_Animation->SetProps("player_idle", 0, 6, 150);

	// runing
	if(m_IsRunning)
		m_Animation->SetProps("player_run", 0, 8, 150);

	// crouching
	if (m_IsCrouching)
		m_Animation->SetProps("player_crouch", 0, 6, 200);

	// jumping
	if (m_IsJumping)
		m_Animation->SetProps("player_jump", 0, 2, 200);

	// falling
	if (m_IsFalling)
		m_Animation->SetProps("player_fall", 0, 2, 350);

	// attacking
	if (m_IsAttacking)
		m_Animation->SetProps("player_attack", 0, 14, 80);
}
