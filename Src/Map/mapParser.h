#pragma once

#include <tinyxml.h>
#include <string>
#include <map>

#include "gameMap.h"
#include "tileLayer.h"

class MapParser
{
public:
	inline static MapParser* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
	}

	inline GameMap* getMaps() const {  }

	bool Load();
	void Clean();

private:
	MapParser() {}
	static MapParser* s_Instance;
	std::map<std::string, GameMap*> m_MapDict;

private:
	bool Parse(std::string id, std::string source);
	TileSet ParseTileSet(TiXmlElement* xmlTileSet);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer);
};