#include <iostream>

#include "GameOverState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string GameOverState::s_gameOverID = "GAME_OVER";

void GameOverState::update()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }
}

void GameOverState::render()
{
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}

bool GameOverState::onEnter()
{
    std::cout << "entering PauseState\n";

    StateParser stateParser;
    stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(nullptr);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    return true;
}

bool GameOverState::onExit()
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

    std::cout << "exiting GameOverState\n";
    return true;
}

std::string GameOverState::getStateID() const
{
    return s_gameOverID;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
}

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
