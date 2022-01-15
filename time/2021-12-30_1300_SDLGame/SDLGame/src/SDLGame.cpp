#include <iostream>
#include "Game.h"

constexpr int FPS        = 60;
constexpr int DELAY_TIME = 1000.0f / FPS;

int main(int /*argc*/, char* /*args*/[])
{
    if(false == TheGame::Instance()->init("Chapter 1", 100, 100, 640, 480, false))
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    while(TheGame::Instance()->running())
    {
        const Uint32 frameStart = SDL_GetTicks();

        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();
        TheGame::Instance()->finalizeIteration();

        const Uint32 frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    TheGame::Instance()->clean();
    return 0;
}
