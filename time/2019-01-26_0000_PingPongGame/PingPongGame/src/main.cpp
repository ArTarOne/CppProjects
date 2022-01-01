#include "stdafx.h"
#include "World.h"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    World world;
    return world.mainLoop();
}
