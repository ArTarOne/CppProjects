#include <iostream>

#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }
}

void PauseState::render()
{
    for(const auto& gameObject : m_gameObjects)
    {
        gameObject->draw();
    }
}

bool PauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("states.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(nullptr);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    return true;
}

bool PauseState::onExit()
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

    TheInputHandler::instance()->reset(); // reset the mouse button states to false

    return true;
}

std::string PauseState::getStateID() const
{
    return s_pauseID;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

void PauseState::s_pauseToMain()
{
    // remove PlayState
    TheGame::instance()->getStateMachine()->popState();
    // then change to MainMenuState
    TheGame::instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
    TheGame::instance()->getStateMachine()->popState();
}
