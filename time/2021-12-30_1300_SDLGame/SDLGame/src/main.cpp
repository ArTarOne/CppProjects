#include <iostream>
#include "Game.h"

constexpr int FPS        = 60;
constexpr int DELAY_TIME = 1000.0f / FPS;

int main(int /*argc*/, char* /*args*/[])
{
    if(false == TheGame::instance()->init("SDL GAME", 100, 100, 640, 480, false))
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    while(TheGame::instance()->running())
    {
        const Uint32 frameStart = SDL_GetTicks();

        TheGame::instance()->handleEvents();
        TheGame::instance()->update();
        TheGame::instance()->render();
        TheGame::instance()->finalizeIteration();

        const Uint32 frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < DELAY_TIME)
        {
            SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
        }
    }

    TheGame::instance()->clean();
    return 0;
}
