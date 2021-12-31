#pragma once

#include "Player.h"
#include "TextureManager.h"
#include "SDL2/SDL.h"

class Game
{
public:
    Game();

    ~Game();

    bool init(const char* title, const int xpos, const int ypos, const int width, int height,
              const bool  fullscreen);

    void render();

    void update();

    void handleEvents();

    void clean() const;

    bool running() const;

private:
    SDL_Window*   m_pWindow      = nullptr;
    SDL_Renderer* m_pRenderer    = nullptr;
    bool          m_bRunning     = false;
    int           m_currentFrame = 0;
    GameObject    m_go;
    Player        m_player;
};
