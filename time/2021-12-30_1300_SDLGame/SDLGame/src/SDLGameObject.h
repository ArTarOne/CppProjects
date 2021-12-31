#pragma once
#include "GameObject.h"
#include "LoaderParams.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);
    void draw() override;
    void update() override;
    void clean() override;

protected:
    int         m_x;
    int         m_y;
    int         m_width;
    int         m_height;
    int         m_currentRow;
    int         m_currentFrame;
    std::string m_textureID;
};
