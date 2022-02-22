#pragma once
#include <vector>

#include "GameObject.h"
#include "Layer.h"

class ObjectLayer : public Layer
{
public:
    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects();

protected:
    ~ObjectLayer() override;

private:
    std::vector<GameObject*> m_gameObjects;
};
