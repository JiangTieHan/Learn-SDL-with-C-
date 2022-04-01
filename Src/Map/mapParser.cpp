#include "mapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
	return Parse("Level1", "assests/maps/map.tmx");
}

void MapParser::Clean()
{
}

bool MapParser::Parse(std::string id, std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		std::cerr << "Failed to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowCount, colCount, tileSize = 0;

	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);

	// Parse Tile sets
	TileSetList tileSets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			tileSets.push_back(ParseTileSet(e));
		}
	}

	GameMap* gameMap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			TileLayer* tileLayer = ParseTileLayer(e, tileSets, tileSize, rowCount, colCount);
			gameMap->GetMapLayers().push_back(tileLayer);
		}
	}

	m_MapDict[id] = gameMap;
	return true;
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
	TiXmlElement* data = nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		data = e;
		break;
	}

	// Parse Layer tile map

	if (data)
	{
		std::string matrix(data->GetText());
		std::istringstream iss(matrix);
		std::string id;

		TileMap tileMap(rowcount, std::vector<int>(colcount, 0));

		for (int row = 0; row < rowcount; row++)
		{
			for (int col = 0; col < colcount; col++)
			{
				getline(iss, id, ',');
				std::stringstream convertor(id);
				convertor >> tileMap[row][col];

				if (!iss.good())
				{
					break;
				}
			}
		}

		return (new TileLayer(tileSize, rowcount, colcount, tileMap, tileSets));
	}

}
