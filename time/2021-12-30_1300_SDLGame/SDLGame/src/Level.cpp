#include "Level.h"
#include "Layer.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::update()
{
    for(auto& layer : m_layers)
    {
        layer->update();
    }
}

void Level::render()
{
    for(auto& layer : m_layers)
    {
        layer->render();
    }
}

std::vector<Tileset>* Level::getTilesets()
{
    return &m_tilesets;
}

std::vector<Layer*>* Level::getLayers()
{
    return &m_layers;
}
