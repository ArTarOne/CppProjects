#include <iostream>

#include "PlayState.h"
#include "Enemy.h"
#include "Game.h"
#include "GameOverState.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Player.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "LevelParser.h"

const std::string PlayState::s_playID = "PLAY";

PlayState::PlayState()
{
}

void PlayState::update()
{
    pLevel->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }

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
        TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
    }
}

void PlayState::render()
{
    pLevel->render();

    // TODO: should be removed
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}

bool PlayState::onEnter()
{
    std::cout << "entering PlayState\n";
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/map1.tmx");
    return true;
}

bool PlayState::onExit()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->clean();
    }
    m_gameObjects.clear();

    for(auto& textureID : m_textureIDList)
    {
        TheTextureManager::Instance()->clearFromTextureMap(textureID);
    }
    m_textureIDList.clear();

    std::cout << "exiting PlayState\n";
    return true;
}

std::string PlayState::getStateID() const
{
    return s_playID;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
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
