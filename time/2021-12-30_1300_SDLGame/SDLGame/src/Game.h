#pragma once

#include "GameStateMachine.h"
#include "SDL2/SDL.h"

class Game
{
public:
    static Game* Instance();

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean() const;
    bool running() const;
    void finalizeIteration();
    void quit();

    SDL_Renderer*     getRenderer() const;
    GameStateMachine* getStateMachine();

private:
    Game();
    ~Game();

private:
    static Game*      s_pInstance;
    SDL_Window*       m_pWindow   = nullptr;
    SDL_Renderer*     m_pRenderer = nullptr;
    bool              m_bRunning  = false;
    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;
