#pragma once
#include <string>
#include <SDL.h>
#include "animation.h"

class SpriteAnimation : public Animation
{
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update(float dt) override;
	void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

	/*inline int GetCurrSpriteRow() const { return m_SpriteRow; }

	inline void SetSpriteRow(int row) { m_SpriteRow = row; }

	inline void IncrSpriteRow() { m_SpriteRow++; }
	inline void DecrSpriteRow() { m_SpriteRow--; }*/

private:
	int m_Speed;
	int m_SpriteRow;
	int m_FrameCount;
	std::string m_TextureID;
};

