﻿#pragma once

#include <vector>

#include "Player.h"
#include "SDL2/SDL.h"

class Game
{
public:
    static Game* Instance();
    bool init(const char* title, const int xpos, const int ypos, const int width, int height,
              const bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean() const;
    bool running() const;
    SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:
    Game();
    ~Game();

private:
    static Game*             s_pInstance;
    SDL_Window*              m_pWindow      = nullptr;
    SDL_Renderer*            m_pRenderer    = nullptr;
    bool                     m_bRunning     = false;
    int                      m_currentFrame = 0;
    std::vector<GameObject*> m_gameObjects;
};

typedef Game TheGame;
