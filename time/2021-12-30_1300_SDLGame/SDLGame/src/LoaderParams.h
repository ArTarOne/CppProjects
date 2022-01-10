#pragma once
#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames = 1,
                 int callbackID = 0, int animSpeed = 0);

    int         getX() const;
    int         getY() const;
    int         getWidth() const;
    int         getHeight() const;
    std::string getTextureID() const;
    int         getNumFrames() const;
    void        setCallback(void (*callback)());
    int         getCallbackID() const;
    int         getAnimSpeed() const;

private:
    int         m_x;
    int         m_y;
    int         m_width;
    int         m_height;
    std::string m_textureID;
    int         m_numFrames;
    void (*     m_callback)();
    int         m_callbackID;
    int         m_animSpeed;
};
