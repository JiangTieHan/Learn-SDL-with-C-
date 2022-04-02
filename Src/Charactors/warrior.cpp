#include "warrior.h"
#include "../Graphic/textureManager.h"
#include "../Inputs/input.h"
#include "../Camera/camera.h"
#include "../Core/engine.h"
#include "../Collision/collisionHandler.h"
#include <SDL.h>

Warrior::Warrior(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip)
	:Character(TextureID,x,y,width,height,flip)
{
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_Collider = new AABB();
	m_Collider->SetBuffer(-60, -20, 0, 0);
	m_IsGrounded = true;

	m_Animation = new Animation();
	if (m_Animation)
	{
		m_Animation->SetProps(TextureID, 0, 6, 150, SDL_FLIP_NONE);
	}

	m_RigidBody = new RigidBody();
	if (m_RigidBody)
	{
		m_RigidBody->SetGravity(3.0f);
	}
}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	if (true)
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
	m_Animation->SetProps("player", 0, 6, 150, SDL_FLIP_NONE);
	m_RigidBody->UnSetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		m_RigidBody->ApplyForceX(5.0f * BACKWARD);
		m_Animation->SetProps("player_run", 0, 8, 150, SDL_FLIP_HORIZONTAL);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		m_RigidBody->ApplyForceX(5.0f * FORWARD);
		m_Animation->SetProps("player_run", 0, 8, 150, SDL_FLIP_NONE);
	}

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

	//m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

	if (m_IsJumping || !m_IsGrounded)
	{
		m_Animation->SetProps("player_jump", 0, 2, 350, SDL_FLIP_NONE);
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update();
}

void Warrior::Clean()
{
	delete m_Animation;
	delete m_RigidBody;
	TextureManager::GetInstance()->Drop(m_TextureID);
}
