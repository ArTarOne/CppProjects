#pragma once

#include <map>
#include <string>

#include "TileLayer.h"
#include "SDL2/SDL.h"

class TextureManager
{
public:
    static TextureManager* instance();

    bool load(const std::string& fileName, const std::string& id, SDL_Renderer* pRenderer);

    void draw(const std::string& id,
              int                x,
              int                y,
              int                width,
              int                height,
              SDL_Renderer*      pRenderer,
              SDL_RendererFlip   flip = SDL_FLIP_NONE);

    void drawFrame(const std::string& id,
                   int                x,
                   int                y,
                   int                width,
                   int                height,
                   int                currentRow,
                   int                currentFrame,
                   SDL_Renderer*      pRenderer,
                   SDL_RendererFlip   flip = SDL_FLIP_NONE);

    void drawTile(const std::string& id,
                  int                margin,
                  int                spacing,
                  int                x,
                  int                y,
                  int                width,
                  int                height,
                  int                currentRow,
                  int                currentFrame,
                  SDL_Renderer*      pRenderer);

    void clearFromTextureMap(const std::string& id);

private:
    TextureManager();

private:
    static TextureManager*              s_pInstance;
    std::map<std::string, SDL_Texture*> m_textureMap;
};

using TheTextureManager = TextureManager;
