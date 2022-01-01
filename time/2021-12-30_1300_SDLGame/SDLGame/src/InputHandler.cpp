﻿#include <iostream>

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

        const int whichOne = event.jaxis.which;

        if(event.type == SDL_JOYAXISMOTION)
        {
            // left stick move left or right
            if(event.jaxis.axis == 0)
            {
                if(event.jaxis.value > m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].first->setX(1);
                }
                else if(event.jaxis.value < -m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].first->setX(-1);
                }
                else
                {
                    m_joystickValues[whichOne].first->setX(0);
                }
            }

            // left stick move up or down
            if(event.jaxis.axis == 1)
            {
                if(event.jaxis.value > m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].first->setY(1);
                }
                else if(event.jaxis.value < -m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].first->setY(-1);
                }
                else
                {
                    m_joystickValues[whichOne].first->setY(0);
                }
            }

            // right stick move left or right
            if(event.jaxis.axis == 3)
            {
                if(event.jaxis.value > m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].second->setX(1);
                }
                else if(event.jaxis.value < -m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].second->setX(-1);
                }
                else
                {
                    m_joystickValues[whichOne].second->setX(0);
                }
            }

            // right stick move up or down
            if(event.jaxis.axis == 4)
            {
                if(event.jaxis.value > m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].second->setY(1);
                }
                else if(event.jaxis.value < -m_joystickDeadZone)
                {
                    m_joystickValues[whichOne].second->setY(-1);
                }
                else
                {
                    m_joystickValues[whichOne].second->setY(0);
                }
            }
        }

        if(event.type == SDL_JOYBUTTONDOWN)
        {
            m_buttonStates[whichOne][event.jbutton.button] = true;
        }

        if(event.type == SDL_JOYBUTTONUP)
        {
            m_buttonStates[whichOne][event.jbutton.button] = false;
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
                // add our pair of joysticks
                m_joystickValues.emplace_back(new Vector2D(0, 0), new Vector2D(0, 0));

                std::vector<bool> tempButtons;
                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                {
                    tempButtons.push_back(false);
                }
                m_buttonStates.push_back(tempButtons);
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

int InputHandler::xvalue(int joy, int stick)
{
    if(!m_joystickValues.empty())
    {
        if(stick == 1)
        {
            return m_joystickValues[joy].first->getX();
        }
        else if(stick == 2)
        {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if(!m_joystickValues.empty())
    {
        if(stick == 1)
        {
            return m_joystickValues[joy].first->getY();
        }
        else if(stick == 2)
        {
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}

bool InputHandler::getButtonState(int joy, int buttonNumber)
{
    return m_buttonStates[joy][buttonNumber];
}

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

InputHandler* InputHandler::s_pInstance = nullptr;
