#pragma once

#include <tinyxml.h>
#include <map>
#include <string>
#include "tileLayer.h"
#include "gameMap.h"

class MapParser
{
public:
	inline MapParser* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
	}

	bool Load();
	void Clean();

	inline GameMap* GetMaps(std::string id) { return m_MapDict[id]; }

private:
	bool Parse(std::string id, std::string source);
	TileSet ParseTileSet(TiXmlElement* xmlTileSet);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tileSets, int tileSize, int rowcount, int colcount);

private:
	MapParser();
	static MapParser* s_Instance;
	std::map<std::string, GameMap*> m_MapDict;
};