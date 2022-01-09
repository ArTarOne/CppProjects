#pragma once
#include <string>

class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames = 1);

    int         getX() const;
    int         getY() const;
    int         getWidth() const;
    int         getHeight() const;
    std::string getTextureID() const;
    int         getNumFrames() const;

private:
    int         m_x;
    int         m_y;
    int         m_width;
    int         m_height;
    std::string m_textureID;
    int         m_numFrames;
};
