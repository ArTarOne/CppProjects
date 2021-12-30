#include <iostream>
#include "Game.h"

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
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    SDL_Surface* pTempSurface = SDL_LoadBMP("assets/animate.bmp");
    m_pTexture                = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    //SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_sourceRectangle.w, &m_sourceRectangle.h);
    m_sourceRectangle.w      = 128;
    m_sourceRectangle.h      = 82;
    m_destinationRectangle.x = 0;
    m_destinationRectangle.y = 0;
    m_sourceRectangle.x      = 0;
    m_sourceRectangle.y      = 0;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    std::cout << "init success\n";
    m_bRunning = true;
    return true;
}

void Game::render() const
{
    // clear the window
    SDL_RenderClear(m_pRenderer);

    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0,
                     nullptr, SDL_FLIP_HORIZONTAL);

    // show the window
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));
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
