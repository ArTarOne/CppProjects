#pragma once
#include <tinyxml2.h>

#include "GameObject.h"
#include "Level.h"

/**
 * \brief read map.tmx. Return Level*
 */
class LevelParser
{
public:
    /**
     * \brief read map.tmx. Return Level*
     * \param levelFile [in] map.tmx file name
     * \return Return Level*
     */
    Level* parseLevel(const char* levelFile);

private:
    static void parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    void        parseTileLayer(tinyxml2::XMLElement*       pTileElement,
                               std::vector<Layer*>*        pLayers,
                               const std::vector<Tileset>* pTilesets) const;
    static void        parseTextures(tinyxml2::XMLElement* pMapProperties);
    static void        parseObjectLayer(tinyxml2::XMLElement* pObjectElement, std::vector<Layer*>* pLayers);
    static GameObject* parseTypedGameObject(tinyxml2::XMLElement* pTypedObject);

private:
    int m_tileSize = 0;
    int m_width    = 0;
    int m_height   = 0;
};
