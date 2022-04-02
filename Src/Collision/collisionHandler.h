#pragma once
#include <SDL.h>
#include <vector>
#include "../Map/tileLayer.h"
#include "../Map/gameMap.h"

class CollisionHandler
{
public:
	bool CheckCollision(const SDL_Rect& a,const SDL_Rect& b) const;
	bool MapCollision(const SDL_Rect& a) const;

	inline static CollisionHandler* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler();
	}

private:
	CollisionHandler();
	static CollisionHandler* s_Instance;

	TileMap m_CollisionTilemap;
	TileLayer* m_CollisionLayer;

};

