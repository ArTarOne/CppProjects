#pragma once

#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
    Player();
    void draw() override;
    void update() override;
    void clean() override;
    void load(const LoaderParams* pParams) override;

private:
    void handleInput();
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const override;
};
