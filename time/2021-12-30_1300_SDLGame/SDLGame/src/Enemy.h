#pragma once
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();
    void draw() override;
    void update() override;
    void clean() override;
    void load(const LoaderParams* pParams) override;
};

class EnemyCreator : public BaseCreator
{
    GameObject* createGameObject() const override;
};
