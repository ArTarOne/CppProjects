#pragma once
#include <vector>

#include "SDL2/SDL.h"

class InputHandler
{
public:
    static InputHandler* Instance();
    void update();
    void clean();
    void initialiseJoysticks();
    bool joysticksInitialised();

private:
    InputHandler();
    ~InputHandler();

private:
    static InputHandler*       s_pInstance;
    std::vector<SDL_Joystick*> m_joysticks;
    bool                       m_bJoysticksInitialised;
};

typedef InputHandler TheInputHandler;
