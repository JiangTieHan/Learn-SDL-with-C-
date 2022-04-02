#pragma once


class Animation
{
public:
	Animation(bool repeat = true) : m_Repeat(repeat), m_IsEnded(false), m_CurrentFrame(0) {}

	virtual void Update(float dt) = 0;

	inline bool GetIsEnded() const { return m_IsEnded; }

	inline int GetCurrFrame() const { return m_CurrentFrame; }

protected:
	bool m_Repeat;
	bool m_IsEnded;
	int m_CurrentFrame;
};
