#include <iostream>

#include "MainMenuState.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string MainMenuState::s_menuID = "MENU";

MainMenuState::MainMenuState() = default;

MainMenuState::~MainMenuState() = default;

void MainMenuState::update()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }
}

void MainMenuState::render()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}

bool MainMenuState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("states.xml", s_menuID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(nullptr); // push back 0 - callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);

    return true;
}

bool MainMenuState::onExit()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->clean();
    }
    m_gameObjects.clear();

    for(const auto& textureID : m_textureIDList)
    {
        TheTextureManager::instance()->clearFromTextureMap(textureID);
    }
    m_textureIDList.clear();

    return true;
}

std::string MainMenuState::getStateID() const
{
    return s_menuID;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for(const auto& gameObject : m_gameObjects)
    {
        if(dynamic_cast<MenuButton*>(gameObject))
        {
            auto* pButton = dynamic_cast<MenuButton*>(gameObject);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void MainMenuState::s_menuToPlay()
{
    TheGame::instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::instance()->quit();
}
