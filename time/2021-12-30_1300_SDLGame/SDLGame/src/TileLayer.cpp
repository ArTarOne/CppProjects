#include <iostream>

#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets)
    : m_numColumns(0),
      m_numRows(0),
      m_tileSize(tileSize),
      m_position(0, 0),
      m_velocity(0, 0),
      m_tilesets(tilesets)
{
    m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize);
    m_numRows    = (TheGame::Instance()->getGameHeight() / m_tileSize);
}

void TileLayer::update()
{
    m_position += m_velocity;
    const auto maxTopLeftXOnMap = (m_tileIDs[0].size() - m_numColumns) * m_tileSize;
    if(m_position.getX() > maxTopLeftXOnMap)
    {
        m_position.setX(maxTopLeftXOnMap);
    }
    m_velocity.setX(1); // TODO
}

void TileLayer::render()
{
    int x  = m_position.getX() / m_tileSize;
    int y  = m_position.getY() / m_tileSize;
    int x2 = static_cast<int>(m_position.getX()) % m_tileSize;
    int y2 = static_cast<int>(m_position.getY()) % m_tileSize;

    for(int i = 0; i < m_numRows; i++)
    {
        int numColumnsRespectMoving;
        if(x2 == 0)
        {
            numColumnsRespectMoving = m_numColumns;
        }
        else
        {
            // increase because of 2 incomplete tiles
            // one on the left, one on the right of screen
            numColumnsRespectMoving = m_numColumns + 1; 
        }

        for(int j = 0; j < numColumnsRespectMoving; j++)
        {
            int id = m_tileIDs[i][j + x];
            if(id == 0)
            {
                continue;
            }
            Tileset tileset = getTilesetByID(id);
            id--;
            TheTextureManager::Instance()->drawTile(tileset.name,
                                                    2,
                                                    2,
                                                    (j * m_tileSize) - x2,
                                                    (i * m_tileSize) - y2,
                                                    m_tileSize,
                                                    m_tileSize,
                                                    (id - (tileset.firstGridID - 1)) / tileset.
                                                    numColumns,
                                                    (id - (tileset.firstGridID - 1)) % tileset.
                                                    numColumns,
                                                    TheGame::Instance()->getRenderer());
        }
    }
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
    m_tileIDs = data;
}

void TileLayer::setTileSize(int tileSize)
{
    m_tileSize = tileSize;
}

Tileset TileLayer::getTilesetByID(int tileID)
{
    for(int i = 0; i < m_tilesets.size(); i++)
    {
        if(i + 1 <= m_tilesets.size() - 1)
        {
            if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
            {
                return m_tilesets[i];
            }
        }
        else
        {
            return m_tilesets[i];
        }
    }

    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}
