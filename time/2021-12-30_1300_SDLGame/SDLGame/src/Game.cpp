﻿#include <iostream>
#include "Game.h"
#include "AnimatedGraphic.h"
#include "Enemy.h"
#include "GameObjectFactory.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "Player.h"
#include "PlayState.h"
#include "SoundManager.h"

Game::Game()  = default;
Game::~Game() = default;

Game* Game::instance()
{
    if(m_pTheGameInstance == nullptr)
    {
        m_pTheGameInstance = new Game();
        return m_pTheGameInstance;
    }
    return m_pTheGameInstance;
}

bool Game::init(const char* title, const int xpos, const int ypos, const int width, const int height, const bool fullscreen)
{
    m_gameWidth  = width;
    m_gameHeight = height;

    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL init fail\n";
        _ASSERT(false);
        return false;
    }

    TheInputHandler::instance()->initialiseJoysticks();

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow == nullptr)
    {
        std::cerr << "window init fail\n";
        _ASSERT(false);
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == nullptr)
    {
        std::cerr << "renderer init fail\n";
        _ASSERT(false);
        return false;
    }

    // This function expects Red, Green, Blue and Alpha as color values
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

    TheGameObjectFactory::instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::instance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    TheSoundManager::instance()->load("boom.wav", "boom", SoundTypeEnum::SOUND_SFX);

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    m_bRunning = true;
    return true;
}

void Game::render() const
{
    SDL_RenderClear(m_pRenderer); // clear to the draw color

    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update() const
{
    m_pGameStateMachine->update();
}

void Game::handleEvents() const
{
    TheInputHandler::instance()->update();

    if(TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}

void Game::clean() const
{
    std::cout << "cleaning game\n";
    TheInputHandler::instance()->clean();
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

bool Game::running() const
{
    return m_bRunning;
}

void Game::finalizeIteration() const
{
    m_pGameStateMachine->destroyRemoveCandidates();
}

void Game::quit()
{
    m_bRunning = false;
}

SDL_Renderer* Game::getRenderer() const
{
    return m_pRenderer;
}

GameStateMachine* Game::getStateMachine() const
{
    return m_pGameStateMachine;
}

int Game::getGameWidth() const
{
    return m_gameWidth;
}

int Game::getGameHeight() const
{
    return m_gameHeight;
}

Game* Game::m_pTheGameInstance = nullptr;
