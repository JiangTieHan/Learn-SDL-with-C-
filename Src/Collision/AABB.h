#pragma once

#include <SDL.h>

typedef SDL_Rect Box;

class AABB
{
public:
	inline Box Get() const { return m_Box; }
	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x,y,w,h }; }

	void Set(int x, int y, int w, int h)
	{
		m_Box = {
		x - m_Buffer.x,
		y - m_Buffer.y,
		w - m_Buffer.w,
		h - m_Buffer.h, };
	}

private:
	Box m_Box;
	Box m_Buffer;
};