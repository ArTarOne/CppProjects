#include "Player.h"
#include "InputHandler.h"
#include "SoundManager.h"

Player::Player() : SDLGameObject()
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);
    handleInput();
    m_currentFrame = static_cast<int>((SDL_GetTicks() / 100) % m_numFrames);
    SDLGameObject::update();
}

void Player::clean()
{
    SDLGameObject::clean();
}

void Player::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
}

void Player::handleInput()
{
    if(TheInputHandler::instance()->joysticksInitialized())
    {
        // stick control
        if(TheInputHandler::instance()->xValue(0, 1) > 0 || TheInputHandler::instance()->xValue(0, 1) < 0)
        {
            m_velocity.setX(1 * TheInputHandler::instance()->xValue(0, 1));
        }
        if(TheInputHandler::instance()->yValue(0, 1) > 0 || TheInputHandler::instance()->yValue(0, 1) < 0)
        {
            m_velocity.setY(1 * TheInputHandler::instance()->yValue(0, 1));
        }
        if(TheInputHandler::instance()->xValue(0, 2) > 0 || TheInputHandler::instance()->xValue(0, 2) < 0)
        {
            m_velocity.setX(1 * TheInputHandler::instance()->xValue(0, 2));
        }
        if(TheInputHandler::instance()->yValue(0, 2) > 0 || TheInputHandler::instance()->yValue(0, 2) < 0)
        {
            m_velocity.setY(1 * TheInputHandler::instance()->yValue(0, 2));
        }

        // button control
        if(TheInputHandler::instance()->getButtonState(0, 3))
        {
            m_velocity.setX(1);
        }
    }

    // mouse control
    if(TheInputHandler::instance()->getMouseButtonState(LEFT))
    {
        const Vector2D vec = TheInputHandler::instance()->getMousePosition();
        m_velocity         = (vec - m_position) / 50;
    }

    // keyboard control
    if(TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_velocity.setX(2);
    }
    if(TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_velocity.setX(-2);
    }
    if(TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        m_velocity.setY(-2);
    }
    if(TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_velocity.setY(2);
    }
    if(TheInputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        TheSoundManager::instance()->playSound("boom", 0);
    }
}

GameObject* PlayerCreator::createGameObject() const
{
    return new Player();
}
