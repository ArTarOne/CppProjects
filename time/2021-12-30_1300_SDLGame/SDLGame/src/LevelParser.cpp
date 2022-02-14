#include <iostream>

#include "LevelParser.h"
#include "Game.h"
#include "TextureManager.h"
#include <cpp-base64/base64.h>
#include <zlib.h>

#include "GameObjectFactory.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "Utils.h"
#include "LoaderParams.h"
#include "C:/Users/marle/Downloads/_bookmarks/Scripts/cpp_utils/tyulenev_debug_utils.hpp" // TYULENEV_DEBUG


/**
 * \brief read level from xml file
 * \param levelFile [in] map.tmx file name
 * \return [out new] pointer to the new class Level
 */
Level* LevelParser::parseLevel(const char* levelFile)
{
    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    Level*                pLevel = new Level();
    tinyxml2::XMLElement* pRoot  = levelDocument.RootElement(); // <map>

    // xml:<map>
    m_tileSize = pRoot->IntAttribute("tilewidth");
    m_width    = pRoot->IntAttribute("width");
    m_height   = pRoot->IntAttribute("height");

    // xml:<map><tileset>
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    // xml:<map><layer>
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
        }
    }

    // xml:<map><properties> - load Textures
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("properties"))
        {
            parseTextures(e);
        }
    }

    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        // xml:<map><objectgroup><object>
        if(e->Value() == std::string("objectgroup"))
        {
            if(e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayer(e, pLevel->getLayers());
            }
        }

        // xml:<map><layer><data>
        if(e->Value() == std::string("layer"))
        {
            if(e->FirstChildElement()->Value() == std::string("data"))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
            }
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
 * \param pTilesetRoot [in] map.tmx:<tileset>
 * \param pTilesets [out]
 */
void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    tinyxml2::XMLDocument blockDocument;
    std::string blockDocumentName = addAssetFolderPrefix(pTilesetRoot->Attribute("source"));
    blockDocument.LoadFile(blockDocumentName.c_str());

    tinyxml2::XMLElement* pBlockRoot = blockDocument.RootElement(); // blocks.tsx:<tileset>

    auto image = pBlockRoot->FirstChildElement();
    TheTextureManager::Instance()->load(addAssetFolderPrefix(image->Attribute("source")),
                                        pBlockRoot->Attribute("name"),
                                        TheGame::Instance()->getRenderer());

    Tileset tileset;
    tileset.width       = image->IntAttribute("width");
    tileset.height      = image->IntAttribute("height");
    tileset.firstGridID = pTilesetRoot->IntAttribute("firstgid");
    tileset.tileWidth   = pBlockRoot->IntAttribute("tilewidth");
    tileset.tileHeight  = pBlockRoot->IntAttribute("tileheight");
    tileset.spacing     = pBlockRoot->IntAttribute("spacing");
    tileset.margin      = pBlockRoot->IntAttribute("margin");
    tileset.name        = pBlockRoot->Attribute("name");
    tileset.numColumns  = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

/**
 * \brief
 * <layer id="1" name="Tile Layer 1" width="60" height="15">
 *  <data encoding="base64" compression="zlib">
 *   w95vwDCnohzeJzVlUlOwzAYhZ0N7FgB6cQBGC
 *  </data>
 * </layer>
 * \param pTileElement [in] xml:<layer>
 * \param pLayers [out]
 * \param pTilesets [in]
 */
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
        std::string        layer_data_encoded_text = utils::trim(text->Value());
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

/**
 * \brief
 * <properties>
 *  <property name="helicopter" value="helicopter.png"/>
 * </properties>
 * \param pMapProperties [in] xml:<properties>
 */
void LevelParser::parseTextures(tinyxml2::XMLElement* pMapProperties)
{
    auto property = pMapProperties->FirstChildElement();
    auto fileName = addAssetFolderPrefix(property->Attribute("value"));
    auto id       = addAssetFolderPrefix(property->Attribute("name"));
    TheTextureManager::Instance()->load(fileName, id, TheGame::Instance()->getRenderer());
}

/**
 * \brief
 * <objectgroup id="3" name="Object Layer 1">
 *  <object id="9" name="Helicopter1" type="Player" x="32" y="322" width="38" height="78">
 *   <properties>
 *    <property name="numFrames" value="4"/>
 *    <property name="textureHeight" value="55"/>
 *    <property name="textureID" value="helicopter"/>
 *    <property name="textureWidth" value="128"/>
 *   </properties>
 *  </object>
 * </objectgroup>
 * \param pObjectElement [in] xml:<map><objectgroup>
 * \param pLayers [out]
 */
void LevelParser::parseObjectLayer(tinyxml2::XMLElement* pObjectElement,
                                   std::vector<Layer*>*  pLayers)
{
    // create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    std::cout << pObjectElement->FirstChildElement()->Value();

    for(auto* e = pObjectElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("object"))
        {
            int         width{};
            int         height{};
            int         numFrames{};
            int         callbackID{};
            int         animSpeed{};
            std::string textureID{};

            int x = e->IntAttribute("x");
            int y = e->IntAttribute("y");

            GameObject* pGameObject = TheGameObjectFactory::Instance()->
                create(e->Attribute("type"));

            for(auto* properties = e->FirstChildElement(); properties != nullptr; properties =
                properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(auto* property = properties->FirstChildElement(); property != nullptr;
                        property       = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                numFrames = property->IntAttribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                height = property->IntAttribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                width = property->IntAttribute("value");
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                callbackID = property->IntAttribute("value");
                            }
                            else if(property->Attribute("name") == std::string("animSpeed"))
                            {
                                animSpeed = property->IntAttribute("value");
                            }
                        }
                    }
                }
            }
            pGameObject->load(new LoaderParams(x,
                                               y,
                                               width,
                                               height,
                                               textureID,
                                               numFrames,
                                               callbackID,
                                               animSpeed));
            TYULENEV_DEBUG(<< TYULENEV_PAIR(pObjectLayer->getGameObjects())); // TYULENEV_DEBUG
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    pLayers->push_back(pObjectLayer);
}
