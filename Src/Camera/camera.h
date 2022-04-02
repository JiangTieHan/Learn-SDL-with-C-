#pragma once
#include "../Physics/vector2D.h"
#include <SDL.h>

#define SCREEN_WIDTH 960
#define SCREEN_HIGHT 640

typedef Vector2D Point;

class Camera
{
public:
	inline static Camera* GetInstance(int width, int height)
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(width,height);
	}

	inline SDL_Rect GetViewBox() const { return m_ViewBox; }
	inline Point GetPosition() const { return m_Position; }
	
	inline void SetTarget(Point* target) { m_Target = target; }

	void Update(float dt);

private:
	Camera(int width, int height);

	static Camera* s_Instance;
	Point* m_Target;
	Point m_Position;
	SDL_Rect m_ViewBox;

	int m_ScreenWidth;
	int m_ScreenHeight;
};

