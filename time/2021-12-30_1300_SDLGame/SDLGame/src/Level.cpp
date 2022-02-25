#include "Level.h"
#include "Layer.h"

Level::Level() = default;

Level::~Level()
{
    for(const Layer* layer : m_layers)
    {
        delete layer;
    }
}

void Level::update() const
{
    for(const auto& layer : m_layers)
    {
        layer->update();
    }
}

void Level::render() const
{
    for(const auto& layer : m_layers)
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
