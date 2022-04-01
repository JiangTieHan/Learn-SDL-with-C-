#include "mapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
	return Parse("Level1", "assests/maps/map.tmx");
}

void MapParser::Clean()
{
}

inline GameMap* MapParser::GetMaps()
{
	return nullptr;
}

bool MapParser::Parse(std::string id, std::string source)
{
	return false;
}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
	TileSet tileSet;

	tileSet.name = xmlTileSet->Attribute("name");
	xmlTileSet->Attribute("firstgid", &tileSet.firstID);
	xmlTileSet->Attribute("tilecount", &tileSet.tileCount);
	tileSet.lastID = tileSet.firstID + tileSet.tileCount - 1;

	xmlTileSet->Attribute("columns", &tileSet.colCount);
	tileSet.rowCount = tileSet.tileCount / tileSet.colCount;
	xmlTileSet->Attribute("tilewidth", &tileSet.tileSize);

	TiXmlElement* image = xmlTileSet->FirstChildElement();
	tileSet.source = image->Attribute("source");

	return tileSet;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tileSets, int tileSize, int rowcount, int colcount)
{
	return nullptr;
}
