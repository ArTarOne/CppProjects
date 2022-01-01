#pragma once
#include <vector>

#include "Vector2D.h"
#include "SDL2/SDL.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance();
    void                 update();
    void                 clean();
    void                 initialiseJoysticks();
    bool                 joysticksInitialised();
    int                  xvalue(int joy, int stick);
    int                  yvalue(int joy, int stick);
    bool                 getButtonState(int joy, int buttonNumber);
    bool                 getMouseButtonState(int buttonNumber);
    const Vector2D&      getMousePosition();

private:
    InputHandler();
    ~InputHandler();

private:
    static InputHandler*       s_pInstance;
    std::vector<SDL_Joystick*> m_joysticks;

    bool m_bJoysticksInitialised;
    /*
     * • Left and right movement on stick one is axis 0
     * • Up and down movement on stick one is axis 1
     * • Left and right movement on stick two is axis 3
     * • Up and down movement on stick two is axis 4
     */
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    const int                                    m_joystickDeadZone = 10000;
    std::vector<std::vector<bool>>               m_buttonStates;

    std::vector<bool> m_mouseButtonStates;
    Vector2D          m_mousePosition;
};

typedef InputHandler TheInputHandler;
