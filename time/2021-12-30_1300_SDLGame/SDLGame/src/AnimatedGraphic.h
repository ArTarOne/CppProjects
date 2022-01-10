#pragma once
#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();

    void draw() override;
    void update() override;
    void clean() override;
    void load(const LoaderParams* pParams) override;

private:
    int m_animSpeed{};
};

class AnimatedGraphicCreator : public BaseCreator
{
    GameObject* createGameObject() const override;
};
