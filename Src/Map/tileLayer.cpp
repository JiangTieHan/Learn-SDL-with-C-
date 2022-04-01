#include "tileLayer.h"
#include "../Graphic/textureManager.h"

TileLayer::TileLayer(int tilesize, int colcount, int rowcount, TileMap tilemap, TileSetList tilesets) :
	m_TileSize(tilesize), m_ColCount(colcount), m_RowCount(rowcount), m_TileMap(tilemap), m_TileSets(tilesets) {

	for (unsigned int i = 0; i < m_TileSets.size(); i++)
		TextureManager::GetInstance()->Load(m_TileSets[i].name, "assets/maps/" + m_TileSets[i].source);
}

void TileLayer::Render()
{
	for (unsigned int i = 0; i < m_RowCount; i++)
	{
		for (unsigned int j = 0; j < m_ColCount; j++)
		{
			int tileID = m_TileMap[i][j];
			if (tileID == 0) continue;
			else
			{
				int ts_index = 0;

				if (m_TileSets.size() > 1)
				{
					for (unsigned int k = 1; k < m_TileSets.size(); k++)
					{
						if (tileID > m_TileSets[k].firstID && tileID < m_TileSets[k].lastID)
						{
							tileID = tileID + m_TileSets[k].tileCount - m_TileSets[k].lastID;
							ts_index = k;
							break;
						}
					}
				}

				TileSet ts = m_TileSets[ts_index];
				int tileRow = tileID / ts.colCount;
				int tileCol = tileID - tileRow * ts.colCount - 1;

				// if the tile is on the last column
				if (tileID % ts.colCount == 0)
				{
					tileRow--;
					tileCol = ts.colCount - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
			}
		}
	}
}

void TileLayer::Update()
{
}
