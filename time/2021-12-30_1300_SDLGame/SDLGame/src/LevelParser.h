#pragma once
#include <tinyxml2.h>

#include "Level.h"

/**
 * \brief A parser for .tmx files and creating levels from them.
 */
class LevelParser
{
public:
    Level* parseLevel(const char* levelFile);

private:
    void parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    void parseTileLayer(tinyxml2::XMLElement*       pTileElement, std::vector<Layer*>* pLayers,
                        const std::vector<Tileset>* pTilesets);
    void parseTextures(tinyxml2::XMLElement* pMapProperties);
    void parseObjectLayer(tinyxml2::XMLElement* pObjectElement, std::vector<Layer*>* pLayers);

private:
    int m_tileSize;
    int m_width;
    int m_height;
};
