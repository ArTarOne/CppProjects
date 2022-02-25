#include <iostream>

#include "GameOverState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }
}

void GameOverState::render()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}

bool GameOverState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("states.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(nullptr);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    return true;
}

bool GameOverState::onExit()
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

std::string GameOverState::getStateID() const
{
    return s_gameOverID;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
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

void GameOverState::s_gameOverToMain()
{
    TheGame::instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
    TheGame::instance()->getStateMachine()->changeState(new PlayState());
}
