#pragma once
#include <vector>

#include "Vector2D.h"
#include "SDL2/SDL.h"

enum MouseButtonsEnum
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* instance();
    void                 update();

    // joysticks
    void  clean() const;
    void  initialiseJoysticks();
    bool  joysticksInitialized() const;
    float xValue(int joy, int stick) const;
    float yValue(int joy, int stick) const;
    bool  getButtonState(int joy, int buttonNumber);

    // mouse
    bool            getMouseButtonState(int buttonNumber) const;
    const Vector2D& getMousePosition() const;
    void            reset();

    // keyboard
    bool isKeyDown(SDL_Scancode key) const;

private:
    InputHandler();
    ~InputHandler();

    // handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(const SDL_Event& event);
    void onMouseButtonDown(const SDL_Event& event);
    void onMouseButtonUp(const SDL_Event& event);

    // handle joysticks events
    void onJoystickAxisMove(const SDL_Event& event) const;
    void onJoystickButtonDown(const SDL_Event& event);
    void onJoystickButtonUp(const SDL_Event& event);

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
