#include <iostream>
#include "Game.h"
#include "Enemy.h"
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
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL init fail\n";
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow == nullptr)
    {
        std::cout << "window init fail\n";
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == nullptr)
    {
        std::cout << "renderer init fail\n";
        return false;
    }

    // This function expects Red, Green, Blue and Alpha as color values
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

    if(!TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
    {
        return false;
    }

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

    std::cout << "init success\n";
    m_bRunning = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); // clear to the draw color

    // loop through our objects and draw them
    for(const auto& m_gameObject : m_gameObjects)
    {
        m_gameObject->draw();
    }

    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
    // loop through and update our objects
    for(const auto& m_gameObject : m_gameObjects)
    {
        m_gameObject->update();
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT: m_bRunning = false;
            break;
        default: break;
        }
    }
}

void Game::clean() const
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

bool Game::running() const
{
    return m_bRunning;
}

Game* Game::s_pInstance = nullptr;
