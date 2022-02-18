#include <iostream>
#include <ostream>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"
#include "Utils.h"

TextureManager* TextureManager::Instance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new TextureManager();
        return s_pInstance;
    }
    return s_pInstance;
}

bool TextureManager::load(const std::string& fileName, const std::string& id,
                          SDL_Renderer*      pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(utils::deepSearch(fileName).c_str());
    if(pTempSurface == nullptr)
    {
        std::cout << "IMG_Load fail, IMG_GetError() = " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    if(pTexture == nullptr)
    {
        std::cout << "SDL_CreateTextureFromSurface fail" << std::endl;
        return false;
    }

    _ASSERT(pTexture);
    m_textureMap[id] = pTexture;
    return true;
}

void TextureManager::draw(const std::string& id, int x, int y, int width, int height,
                          SDL_Renderer*      pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x  = 0;
    srcRect.y  = 0;
    srcRect.w  = destRect.w = width;
    srcRect.h  = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::drawFrame(const std::string& id, int x, int y, int width, int height,
                               int currentRow, int currentFrame, SDL_Renderer* pRenderer,
                               SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x  = width * currentFrame;      // One sounds more natural to use the first row,
    srcRect.y  = height * (currentRow - 1); // rather than the zeroth row).
    srcRect.w  = destRect.w = width;
    srcRect.h  = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    _ASSERT(m_textureMap[id]);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width,
                              int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x  = margin + (spacing + width) * currentFrame;
    srcRect.y  = margin + (spacing + height) * currentRow;
    srcRect.w  = destRect.w = width;
    srcRect.h  = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
}

TextureManager::TextureManager() = default;

TextureManager* TextureManager::s_pInstance = nullptr;
