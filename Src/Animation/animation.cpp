#include "animation.h"
#include "../Graphic/textureManager.h"

Animation::Animation()
{

}

void Animation::Update()
{
	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimSpeed = animSpeed;
}
