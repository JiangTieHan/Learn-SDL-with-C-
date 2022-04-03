#pragma once

#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include "animation.h"

struct Sequence
{
	int Speed;
	int FrameCount;
	int Width, Height;
	std::vector<std::string> TextureIDs;
};

class SeqAnimation : Animation
{
public:
	SeqAnimation(bool repeat = true);

	virtual void Update(float dt) override;
	bool Parse(const std::string &source);
	void SetCurrentSeq(const std::string &seqID);
	inline void SetRepeat(bool repeat) { m_Repeat = repeat; }
	void DrawFrame(float x, float y, float xScale = 1.0f, float yScale = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	Sequence m_CurrentSeq;
	std::map<std::string, Sequence> m_SeqMap;
};

