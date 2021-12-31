#include <iostream>
#include "Game.h"

int main(int /*argc*/, char* /*args*/[])
{
    if(false == TheGame::Instance()->init("Chapter 1", 100, 100, 640, 480, false))
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    while(TheGame::Instance()->running())
    {
        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();
        SDL_Delay(10); // add the delay
    }

    TheGame::Instance()->clean();
    return 0;
}
