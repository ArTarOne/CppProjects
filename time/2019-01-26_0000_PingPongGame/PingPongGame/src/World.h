#pragma once
#include "Core.h"
#include "WorldSettings.h"
#include "Scene.h"

class World
{
    std::shared_ptr<WorldSettings> worldSettings;
    Core core;
    Scene scene;

public:
    World();
    void handleEvents();
    int mainLoop();
};
