#pragma once
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);
    void draw() override;
    void update() override;
    void clean() override;

protected:
    Vector2D    m_position;
    Vector2D    m_velocity;
    Vector2D    m_acceleration;
    int         m_width;
    int         m_height;
    int         m_currentRow;
    int         m_currentFrame;
    std::string m_textureID;
};
