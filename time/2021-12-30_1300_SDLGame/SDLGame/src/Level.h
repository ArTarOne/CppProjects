#pragma once
#include <string>
#include <vector>

class Layer;

struct Tileset
{
    int         firstGridID;
    int         tileWidth;
    int         tileHeight;
    int         spacing;
    int         margin;
    int         width;
    int         height;
    int         numColumns;
    std::string name;
};

class Level
{
public:
    ~Level();

    void                  update() const;
    void                  render() const;
    std::vector<Tileset>* getTilesets();
    std::vector<Layer*>*  getLayers();

private:
    friend class LevelParser; // LevelParser has access to the private constructor of Level
    Level();

private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer*>  m_layers;
};
