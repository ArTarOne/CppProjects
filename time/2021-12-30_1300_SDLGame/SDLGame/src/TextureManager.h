#pragma once

#include <map>
#include <string>

#include "SDL2/SDL.h"

class TextureManager
{
public:
    static TextureManager* Instance()
    {
        if(s_pInstance == nullptr)
        {
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
        return s_pInstance;
    }

    bool load(const std::string& fileName, const std::string& id, SDL_Renderer* pRenderer);

    void draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* pRenderer,
              SDL_RendererFlip   flip = SDL_FLIP_NONE);

    void drawFrame(const std::string& id, int x, int y, int width, int height, int currentRow,
                   int                currentFrame, SDL_Renderer* pRenderer,
                   SDL_RendererFlip   flip = SDL_FLIP_NONE);

private:
    TextureManager();
    static TextureManager*              s_pInstance;
    std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;
