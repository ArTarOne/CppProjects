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

    // joysticks
    void clean();
    void initialiseJoysticks();
    bool joysticksInitialized();
    int  xvalue(int joy, int stick);
    int  yvalue(int joy, int stick);
    bool getButtonState(int joy, int buttonNumber);

    // mouse
    bool            getMouseButtonState(int buttonNumber);
    const Vector2D& getMousePosition();
    void            reset();

    // keyboard
    bool isKeyDown(SDL_Scancode key);

private:
    InputHandler();
    ~InputHandler();

    // handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

private:
    static InputHandler*       s_pTheInputHandlerInstance;
    std::vector<SDL_Joystick*> m_joysticks;

    bool m_bJoysticksInitialized;
    /*
     * • Left and right movement on stick one is axis 0
     * • Up and down movement on stick one is axis 1
     * • Left and right movement on stick two is axis 3
     * • Up and down movement on stick two is axis 4
     */
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    const int                                    m_joystickDeadZone = 10000;
    std::vector<std::vector<bool>>               m_buttonStates;

    std::vector<int> m_mouseButtonStates;
    Vector2D         m_mousePosition;

    const Uint8* m_pKeystates = nullptr;
};

using TheInputHandler = InputHandler;
