#include "Enemy.h"
#include "SDL2/SDL.h"

Enemy::Enemy() = default;

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    m_currentFrame = static_cast<int>((SDL_GetTicks() / 100) % m_numFrames);

    if(m_position.getY() < 0)
    {
        m_velocity.setY(2);
    }
    else if(m_position.getY() > 400)
    {
        m_velocity.setY(-2);
    }

    SDLGameObject::update();
}

void Enemy::clean()
{
    SDLGameObject::clean();
}

void Enemy::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    m_velocity.setY(2);
}

GameObject* EnemyCreator::createGameObject() const
{
    return new Enemy();
}
