#include "warrior.h"
#include "../Graphic/textureManager.h"
#include <SDL.h>

Warrior::Warrior(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip)
	:Character(TextureID,x,y,width,height,flip)
{
	m_Row = 0;
	m_Frame = 0;
	m_FrameCount = 6;
	m_AnimationSpeed = 120;
}

void Warrior::Draw()
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

void Warrior::Update(float dt)
{
	m_Frame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}
