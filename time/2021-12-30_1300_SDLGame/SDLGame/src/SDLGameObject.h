#pragma once
#include <SDL2/SDL_render.h>

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject();
    void      draw() override;
    void      update() override;
    void      clean() override;
    Vector2D& getPosition();
    int       getWidth() const;
    int       getHeight() const;
    void      load(const LoaderParams* pParams) override;

protected:
    Vector2D         m_position;
    Vector2D         m_velocity;
    Vector2D         m_acceleration;
    int              m_width{};
    int              m_height{};
    int              m_currentRow{};
    int              m_currentFrame{};
    int              m_numFrames{};
    std::string      m_textureID;
    SDL_RendererFlip m_flip;
};
