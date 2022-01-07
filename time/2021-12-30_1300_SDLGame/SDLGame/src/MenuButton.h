#pragma once
#include "LoaderParams.h"
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams* pParams);
    void draw() override;
    void update() override;
    void clean() override;

private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };
};
