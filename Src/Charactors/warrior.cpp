#include "warrior.h"
#include "../Graphic/textureManager.h"
#include "../Inputs/input.h"
#include <SDL.h>

Warrior::Warrior(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip)
	:Character(TextureID,x,y,width,height,flip)
{
	m_Animation = new Animation();
	if (m_Animation)
	{
		m_Animation->SetProps(TextureID, 0, 6, 150, SDL_FLIP_NONE);
	}

	m_RigidBody = new RigidBody();
}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
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

	m_RigidBody->Update(dt);
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update();
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}
