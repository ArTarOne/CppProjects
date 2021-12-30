#pragma once

#include "SDL2/SDL.h"

class Game
{
public:
    Game();

    ~Game();

    bool init(const char* title, const int xpos, const int ypos, const int width, int height,
              const bool  fullscreen);

    void render() const;

    void update();

    void handleEvents();

    void clean() const;

    bool running() const;

private:
    SDL_Window*   m_pWindow   = nullptr;
    SDL_Renderer* m_pRenderer = nullptr;
    bool          m_bRunning  = false;
    SDL_Texture*  m_pTexture;             // the new SDL_Texture variable
    SDL_Rect      m_sourceRectangle;      // the first rectangle
    SDL_Rect      m_destinationRectangle; // another rectangle
};
