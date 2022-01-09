#include <iostream>

#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }
}

void PlayState::render()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}

bool PlayState::onEnter()
{
    if(!TheTextureManager::Instance()->load("assets/helicopter.png",
                                            "helicopter",
                                            TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* player = new Player(new LoaderParams(100, 100, 128, 55, "helicopter"));
    m_gameObjects.push_back(player);

    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");

    std::cout << "exiting PlayState\n";
    return true;
}

std::string PlayState::getStateID() const
{
    return s_playID;
}
