#pragma once

#include "GameStateMachine.h"
#include "SDL2/SDL.h"

class Game
{
public:
    static Game* instance();

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render() const;
    void update() const;
    void handleEvents() const;
    void clean() const;
    bool running() const;
    void finalizeIteration() const;
    void quit();

    SDL_Renderer*     getRenderer() const;
    GameStateMachine* getStateMachine() const;
    int               getGameWidth() const;
    int               getGameHeight() const;

private:
    Game();
    ~Game();

private:
    static Game*      m_pTheGameInstance;
    SDL_Window*       m_pWindow   = nullptr;
    SDL_Renderer*     m_pRenderer = nullptr;
    bool              m_bRunning  = false;
    GameStateMachine* m_pGameStateMachine{};
    int               m_gameWidth{};
    int               m_gameHeight{};
};

using TheGame = Game;
