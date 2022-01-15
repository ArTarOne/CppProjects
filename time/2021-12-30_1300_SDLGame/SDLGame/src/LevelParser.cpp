#include "LevelParser.h"
#include "Game.h"
#include "TextureManager.h"
#include <base64.h>
#include <zlib.h>

#include "TileLayer.h"

Level* LevelParser::parseLevel(const char* levelFile)
{
    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    Level*                pLevel = new Level();
    tinyxml2::XMLElement* pRoot  = levelDocument.RootElement();

    m_tileSize = pRoot->IntAttribute("tilewidth");
    m_width    = pRoot->IntAttribute("width");
    m_height   = pRoot->IntAttribute("height");

    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"),
                                        pTilesetRoot->Attribute("name"),
                                        TheGame::Instance()->getRenderer());

    // TODO - in this example we read only the map file. But block files also should be read.
    // see next files:
    //   blocks1.tsx
    //   blocks2.tsx

    // my version // TODO
    // <tileset firstgid="1" source="blocks1.tsx"/> 

    // example version
    // <tileset firstgid="1" name="blocks1" tilewidth="32" tileheight="32" spacing="2" margin="2">
    //     <image source="blocks1.png" width="614" height="376"/>
    // </tileset>

    Tileset tileset;
    tileset.width       = pTilesetRoot->FirstChildElement()->IntAttribute("width");
    tileset.height      = pTilesetRoot->FirstChildElement()->IntAttribute("height");
    tileset.firstGridID = pTilesetRoot->IntAttribute("firstgid");
    tileset.tileWidth   = pTilesetRoot->IntAttribute("tilewidth");
    tileset.tileHeight  = pTilesetRoot->IntAttribute("tileheight");
    tileset.spacing     = pTilesetRoot->IntAttribute("spacing");
    tileset.margin      = pTilesetRoot->IntAttribute("margin");
    tileset.name        = pTilesetRoot->Attribute("name");
    tileset.numColumns  = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement* pTileElement, std::vector<Layer*>* pLayers,
                                 const std::vector<Tileset>* pTilesets)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    // tile data
    std::vector<std::vector<int>> data;
    std::string                   decodedIDs;
    tinyxml2::XMLElement*         pDataNode{};

    for(tinyxml2::XMLElement* e = pTileElement->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }

    for(tinyxml2::XMLNode* e = pDataNode->FirstChild(); e != nullptr; e = e->NextSibling())
    {
        tinyxml2::XMLText* text = e->ToText();
        std::string        t    = text->Value();
        decodedIDs              = base64_decode(t);
    }

    // uncompress zlib compression
    uLongf                numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);

    uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());
    std::vector<int> layerRow(m_width);

    for(int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }
    for(int rows = 0; rows < m_height; rows++)
    {
        for(int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}
