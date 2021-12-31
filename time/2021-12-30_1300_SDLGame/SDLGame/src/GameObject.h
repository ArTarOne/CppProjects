#pragma once

#include <string>
#include "SDL2/SDL.h"

class GameObject
{
public:
    void load(int x, int y, int width, int height, const std::string& textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean();

protected:
    std::string m_textureID;
    int         m_currentFrame;
    int         m_currentRow;
    int         m_x;
    int         m_y;
    int         m_width;
    int         m_height;
};
