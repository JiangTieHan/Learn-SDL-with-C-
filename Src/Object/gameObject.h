#pragma once
#include "IObject.h"
#include "../Physics/transform.h"
#include <SDL.h>

typedef Vector2D Point;

class GameObject :public IObject
{
public:
	GameObject(std::string TextureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) :
		m_TextureID(TextureID),
		m_Width(width),
		m_Height(height),
		m_Flip(flip)
	{
		m_Transform = new Transform(x, y);

		float px = x + width / 2;
		float py = y + height / 2;
		m_Origin = new Point(px, py);
	}
		

	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

	inline Point* GetOrigin() const { return m_Origin; }

protected:
	Transform* m_Transform;
	int m_Width, m_Height;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
	Point* m_Origin;

};
