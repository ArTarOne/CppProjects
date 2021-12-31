#pragma once
#include "LoaderParams.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);
    void draw() override;
    void update() override;
    void clean() override;
};
