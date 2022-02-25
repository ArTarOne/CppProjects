#pragma once
#include <vector>

#include "GameObject.h"
#include "Layer.h"

class ObjectLayer : public Layer
{
public:
    void update() override;
    void render() override;

    std::vector<GameObject*>* getGameObjects();

protected:
    ~ObjectLayer() override;

private:
    std::vector<GameObject*> m_gameObjects;
};
