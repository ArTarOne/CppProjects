﻿#include <iostream>

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
    m_pLevel->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
}

void PlayState::render()
{
    m_pLevel->render();
}

bool PlayState::onEnter()
{
    LevelParser levelParser;
    m_pLevel = levelParser.parseLevel(utils::deepSearch("map.tmx").c_str());
    return true;
}

bool PlayState::onExit() // TODO never called. Error prone
{
    delete m_pLevel;

    for(auto& textureID : m_textureIDList)
    {
        TheTextureManager::Instance()->clearFromTextureMap(textureID);
    }
    m_textureIDList.clear();

    return true;
}

std::string PlayState::getStateID() const
{
    return s_playID;
}
