#pragma once

#include "layer.h"
#include <string>
#include <vector>

struct TileSet
{
	int firstID, lastID;
	int rowCount, colCount;
	int tileCount, tileSize;
	std::string name, source;
};

typedef std::vector<TileSet> TileSetList;
typedef std::vector<std::vector<int> > TileMap;

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tileSets);
	virtual void Render() override;
	virtual void Update() override;

	inline TileMap GetTileMap() const { return m_TileMap; }

private:
	int m_TileSize;
	int m_RowCount, m_ColCount;

	TileMap m_TileMap;
	TileSetList m_TileSets;
};