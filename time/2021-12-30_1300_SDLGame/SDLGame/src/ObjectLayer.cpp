#include "ObjectLayer.h"
#include "Game.h"
#include "GameOverState.h"
#include "SDLGameObject.h"

bool checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    const int leftA   = p1->getPosition().getX();
    const int rightA  = p1->getPosition().getX() + p1->getWidth();
    const int topA    = p1->getPosition().getY();
    const int bottomA = p1->getPosition().getY() + p1->getHeight();

    //Calculate the sides of rect B
    const int leftB   = p2->getPosition().getX();
    const int rightB  = p2->getPosition().getX() + p2->getWidth();
    const int topB    = p2->getPosition().getY();
    const int bottomB = p2->getPosition().getY() + p2->getHeight();

    //If any of the sides from A are outside of B
    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }

    return true;
}

std::vector<GameObject*>* ObjectLayer::getGameObjects()
{
    return &m_gameObjects;
}

ObjectLayer::~ObjectLayer()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->clean();
    }
    m_gameObjects.clear();
}

void ObjectLayer::update()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }

    if(m_gameObjects.size() < 2)
    {
        return;
    }

    if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
    {
        TheGame::instance()->getStateMachine()->changeState(new GameOverState());
    }
}

void ObjectLayer::render()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}
