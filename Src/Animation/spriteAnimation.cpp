#include "spriteAnimation.h"
#include "../Graphic/textureManager.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat), m_FrameCount(1)
{
}

void SpriteAnimation::Update(float dt)
{
	m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
	m_Speed = speed;
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
}
