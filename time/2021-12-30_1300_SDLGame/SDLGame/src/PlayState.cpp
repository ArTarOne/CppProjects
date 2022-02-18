#include <iostream>

#include "PlayState.h"
#include "Game.h"
#include "GameOverState.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "TextureManager.h"
#include "LevelParser.h"
#include "Utils.h"

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
}

void PlayState::render()
{
    pLevel->render();
}

bool PlayState::onEnter()
{
    std::cout << "entering PlayState\n";
    LevelParser levelParser;
    pLevel = levelParser.parseLevel(utils::deepSearch("map1.tmx").c_str());
    return true;
}

bool PlayState::onExit()
{
    // TODO delegate to Level* pLevel
    //for(auto& gameObject : m_gameObjects)
    //{
    //    gameObject->clean();
    //}
    //m_gameObjects.clear();

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
