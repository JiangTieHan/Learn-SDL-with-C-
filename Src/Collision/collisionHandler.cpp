#include "collisionHandler.h"
#include "../Core/engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
	m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetGameMap()->GetMapLayers().front();
	m_CollisionTilemap = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) const
{
	bool isXOverlapped = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool isYOverlapped = (a.y < b.y + b.h) && (a.y + a.h > b.y);

	return isXOverlapped && isYOverlapped;
}

bool CollisionHandler::MapCollision(const SDL_Rect& a) const
{
	int tileSize = 32;
	int RowCount = 20;
	int ColCount = 60;

	int left_tile = a.x / tileSize;
	int right_tile = (a.x + a.w) / tileSize;
	int top_tile = a.y / tileSize;
	int bottom_tile = (a.y + a.h) / tileSize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount - 1) right_tile = ColCount - 1;
	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount - 1) bottom_tile = RowCount - 1;

	for (int i = left_tile; i <= right_tile; ++i)
	{
		for (int j = top_tile; j <= bottom_tile; ++j)
		{
			if (m_CollisionTilemap[j][i] > 0)
				return true;

		}
	}
	return false;
}
