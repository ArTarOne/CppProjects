#include <iostream>

#include "GameOverState.h"
#include "AnimatedGraphic.h"
#include "Game.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
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
    if(!TheTextureManager::Instance()->load("assets/gameover.png",
                                            "gameovertext",
                                            TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TheTextureManager::Instance()->load("assets/main.png",
                                            "mainbutton",
                                            TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TheTextureManager::Instance()->load("assets/restart.png",
                                            "restartbutton",
                                            TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    // TODO - memory leak with LoaderParams. Move them from heap to stack.
    GameObject* gameOverText = new AnimatedGraphic(
        new LoaderParams(200, 100, 190, 30, "gameovertext", 2),
        2);
    GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"),
                                         s_gameOverToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"),
                                         s_restartPlay);
    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering PauseState\n";
    return true;
}

bool GameOverState::onExit()
{
    return true;
}

std::string GameOverState::getStateID() const
{
    return s_gameOverID;
}

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
