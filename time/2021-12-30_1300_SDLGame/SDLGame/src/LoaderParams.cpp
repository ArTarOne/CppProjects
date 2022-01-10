#include "LoaderParams.h"

LoaderParams::LoaderParams(int x, int         y, int width, int height, std::string textureID,
                           int numFrames, int callbackID, int animSpeed)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID),
      m_numFrames(numFrames), m_callbackID(callbackID), m_animSpeed(animSpeed)
{
}

int LoaderParams::getX() const
{
    return m_x;
}

int LoaderParams::getY() const
{
    return m_y;
}

int LoaderParams::getWidth() const
{
    return m_width;
}

int LoaderParams::getHeight() const
{
    return m_height;
}

std::string LoaderParams::getTextureID() const
{
    return m_textureID;
}

int LoaderParams::getNumFrames() const
{
    return m_numFrames;
}

void LoaderParams::setCallback(void (*callback)())
{
    m_callback = callback;
}

int LoaderParams::getCallbackID() const
{
    return m_callbackID;
}

int LoaderParams::getAnimSpeed() const
{
    return m_animSpeed;
}
