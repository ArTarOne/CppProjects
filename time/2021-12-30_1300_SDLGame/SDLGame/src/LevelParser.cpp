#include "LevelParser.h"
#include "Game.h"
#include "TextureManager.h"
#include <base64.h>
#include <zlib.h>

#include "TileLayer.h"

/**
 * \brief read level from xml file
 * \param levelFile - *.tmx file name
 * \return pointer to the new level
 */
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

inline std::string addAssetFolderPrefix(const std::string& filename)
{
    // TODO hardcoded assets folder name
    return std::string("assets/") + filename;
}

/**
 * \brief read <tileset> section for *.map file. And file of blocks like *.tsx
 *
 * map.tmx:
 * <tileset firstgid="1" source="blocks1.tsx"/>
 *
 * blocks.tsx:
 * <tileset version="1.5" tiledversion="1.7.2" name="blocks1" tilewidth="32" tileheight="32"
 *   spacing="2" margin="2" tilecount="198" columns="18">
 *     <image source="blocks1.png" width="614" height="376"/>
 * </tileset>
 *
 * \param pTilesetRoot <tileset> tag
 * \param pTilesets [out] vector to store tilesets
 */
void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    tinyxml2::XMLDocument blockDocument;
    std::string blockDocumentName = addAssetFolderPrefix(pTilesetRoot->Attribute("source"));
    blockDocument.LoadFile(blockDocumentName.c_str());

    tinyxml2::XMLElement* pBlockRoot = blockDocument.RootElement();

    TheTextureManager::Instance()->load(
        addAssetFolderPrefix(pBlockRoot->FirstChildElement()->Attribute("source")),
        pBlockRoot->Attribute("name"),
        TheGame::Instance()->getRenderer());

    Tileset tileset;
    tileset.width       = pBlockRoot->FirstChildElement()->IntAttribute("width");
    tileset.height      = pBlockRoot->FirstChildElement()->IntAttribute("height");
    tileset.firstGridID = pTilesetRoot->IntAttribute("firstgid");
    tileset.tileWidth   = pBlockRoot->IntAttribute("tilewidth");
    tileset.tileHeight  = pBlockRoot->IntAttribute("tileheight");
    tileset.spacing     = pBlockRoot->IntAttribute("spacing");
    tileset.margin      = pBlockRoot->IntAttribute("margin");
    tileset.name        = pBlockRoot->Attribute("name");
    tileset.numColumns  = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

// TODO - move to utils folder
// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
std::string specialTrim(const std::string& dirtyString)
{
    std::string resultString = dirtyString;
    resultString.erase(resultString.begin(),
                       std::find_if(resultString.begin(),
                                    resultString.end(),
                                    [](unsigned char ch)
                                    {
                                        return !std::isspace(ch);
                                    }));

    // TODO: magic - fragile code
    resultString.erase(std::find_if(resultString.rbegin(),
                                    resultString.rend(),
                                    [](unsigned char ch)
                                    {
                                        return (ch == '=');
                                    }).base(),
                       resultString.end());

    return resultString;
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
        tinyxml2::XMLText* text                    = e->ToText();
        std::string        layer_data_encoded_text = specialTrim(text->Value());
        decodedIDs                                 = base64_decode(layer_data_encoded_text);
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
