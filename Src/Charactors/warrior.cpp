#include "warrior.h"
#include "../Graphic/textureManager.h"
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
	m_RigidBody->Update(0.1);
	m_Transform->Translate(m_RigidBody->GetPosition());

	m_Animation->Update();
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}
