#pragma once

#include <string>

#include "SDLGameObject.h"
#include "SDL2/SDL.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);
    void draw() override;
    void update() override;
    void clean() override;
};
