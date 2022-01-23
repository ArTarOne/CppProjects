#include <iostream>
#include "Game.h"
#include "AnimatedGraphic.h"
#include "Enemy.h"
#include "GameObjectFactory.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "Player.h"
#include "PlayState.h"
#include "TextureManager.h"

Game::Game()  = default;
Game::~Game() = default;

Game* Game::Instance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new Game();
        return s_pInstance;
    }
    return s_pInstance;
}

bool Game::init(const char* title, const int xpos, const int ypos, const int width, int height,
                const bool  fullscreen)
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
        return false;
    }

    TheInputHandler::Instance()->initialiseJoysticks();

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow == nullptr)
    {
        std::cerr << "window init fail\n";
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == nullptr)
    {
        std::cerr << "renderer init fail\n";
        return false;
    }

    // This function expects Red, Green, Blue and Alpha as color values
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    std::cout << "init success\n";
    m_bRunning = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); // clear to the draw color

    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}

void Game::clean() const
{
    std::cout << "cleaning game\n";
    TheInputHandler::Instance()->clean();
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

bool Game::running() const
{
    return m_bRunning;
}

void Game::finalizeIteration()
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

GameStateMachine* Game::getStateMachine()
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

Game* Game::s_pInstance = nullptr;
