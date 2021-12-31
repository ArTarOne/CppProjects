#include <iostream>
#include "Game.h"
#include <SDL2\SDL_image.h>

Game::Game()  = default;
Game::~Game() = default;

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

    m_go.load(100, 100, 128, 82, "animate");
    m_player.load(300, 300, 128, 82, "animate");

    std::cout << "init success\n";
    m_bRunning = true;
    return true;
}

void Game::render()
{
    // clear the window
    SDL_RenderClear(m_pRenderer);

    m_go.draw(m_pRenderer);
    m_player.draw(m_pRenderer);

    // show the window
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_go.update();
    m_player.update();
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
