#include "ObjectLayer.h"
#include "Game.h"
#include "GameOverState.h"
#include "SDLGameObject.h"

bool checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA   = p1->getPosition().getX();
    int rightA  = p1->getPosition().getX() + p1->getWidth();
    int topA    = p1->getPosition().getY();
    int bottomA = p1->getPosition().getY() + p1->getHeight();

    //Calculate the sides of rect B
    int leftB   = p2->getPosition().getX();
    int rightB  = p2->getPosition().getX() + p2->getWidth();
    int topB    = p2->getPosition().getY();
    int bottomB = p2->getPosition().getY() + p2->getHeight();

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
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->clean();
    }
    m_gameObjects.clear();
}

void ObjectLayer::update()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }

    if(m_gameObjects.size() < 2)
    {
        return;
    }

    if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
                      dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
    {
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
    }
}

void ObjectLayer::render()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}
