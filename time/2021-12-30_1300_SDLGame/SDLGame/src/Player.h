﻿#pragma once

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);
    void draw() override;
    void update() override;
    void clean() override;

private:
    void handleInput();
};
