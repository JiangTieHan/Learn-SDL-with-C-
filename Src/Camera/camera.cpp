#include "camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt)
{
	if(m_Target)
	{
		m_ViewBox.x = m_Target->X - m_ScreenWidth / 2;
		m_ViewBox.y = m_Target->Y - m_ScreenHeight / 2;

		if (m_ViewBox.x < 0) m_ViewBox.x = 0;
		if (m_ViewBox.y < 0) m_ViewBox.y = 0;
		if (m_ViewBox.x > (2 * m_ScreenWidth - m_ViewBox.w)) m_ViewBox.x = 2 * m_ScreenWidth - m_ViewBox.w;
		if (m_ViewBox.y > (m_ScreenHeight - m_ViewBox.h)) m_ViewBox.y = m_ScreenHeight - m_ViewBox.h;

		m_Position = Point(m_ViewBox.x, m_ViewBox.y);
	}
}

Camera::Camera(int screenWidth, int screenHeight) :
	m_ScreenWidth(screenWidth),
	m_ScreenHeight(screenHeight)
{
	m_ViewBox = { 0, 0, screenWidth, screenHeight };
}
