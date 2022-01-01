#include <iostream>

#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::Instance()
{
    if(s_pInstance == 0)
    {
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
}

void InputHandler::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            TheGame::Instance()->quit();
        }
    }
}

void InputHandler::clean()
{
    if(m_bJoysticksInitialised)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

void InputHandler::initialiseJoysticks()
{
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if(SDL_NumJoysticks() > 0)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if(SDL_JoystickOpen(i) != nullptr)
            {
                m_joysticks.push_back(joy);
            }
            else
            {
                std::cout << "SDL_JoystickOpen" << "(" << i << ")" << " returns error: " <<
                    SDL_GetError();
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        std::cout << "Initialized " << m_joysticks.size() << " joystick(s)\n";
    }
    else
    {
        std::cout << "Joystick(s) not found\n";
        m_bJoysticksInitialised = false;
    }
}

bool InputHandler::joysticksInitialised()
{
    return m_bJoysticksInitialised;
}

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

InputHandler* InputHandler::s_pInstance = nullptr;
