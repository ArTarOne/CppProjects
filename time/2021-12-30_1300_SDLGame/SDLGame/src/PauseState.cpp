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
    for(auto& gameObject : m_gameObjects)
    {
        gameObject->update();
    }
}

void PauseState::render()
{
    for(auto& gameObject : m_gameObjects)
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

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit()
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

    TheInputHandler::Instance()->reset(); // reset the mouse button states to false

    std::cout << "exiting PauseState\n";
    return true;
}

std::string PauseState::getStateID() const
{
    return s_pauseID;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

void PauseState::s_pauseToMain()
{
    // remove PlayState
    TheGame::Instance()->getStateMachine()->popState();
    // then change to MainMenuState
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}
