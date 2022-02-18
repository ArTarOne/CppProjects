#include <iostream>

#include "MainMenuState.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string MainMenuState::s_menuID = "MENU";

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }
}

void MainMenuState::render()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}

bool MainMenuState::onEnter()
{
    std::cout << "entering MainMenuState\n";

    StateParser stateParser;
    stateParser.parseState("menu_states.xml", s_menuID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(nullptr); // push back 0 - callbackID start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);

    return true;
}

bool MainMenuState::onExit()
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

    std::cout << "exiting MainMenuState\n";
    return true;
}

std::string MainMenuState::getStateID() const
{
    return s_menuID;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for(auto& gameObject : m_gameObjects)
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
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}
