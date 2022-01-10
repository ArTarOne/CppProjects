#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton()
    : m_callback(nullptr), m_bReleased(false), m_callbackID(0)
{
    m_currentFrame = MOUSE_OUT; // start at frame 0
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D pMousePos = TheInputHandler::Instance()->getMousePosition();
    if(pMousePos.getX() < (m_position.getX() + m_width) && pMousePos.getX() > m_position.getX() &&
        pMousePos.getY() < (m_position.getY() + m_height) && pMousePos.getY() > m_position.getY())
    {
        m_currentFrame = MOUSE_OVER;
        if(TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;
            _ASSERT(m_callback);
            m_callback();
            m_bReleased = false;
        }
        else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_bReleased    = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}

void MenuButton::setCallback(void (*callback)())
{
    m_callback = callback;
}

int MenuButton::getCallbackID()
{
    return m_callbackID;
}

void MenuButton::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    m_callbackID   = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;
}

GameObject* MenuButtonCreator::createGameObject() const
{
    return new MenuButton();
}
