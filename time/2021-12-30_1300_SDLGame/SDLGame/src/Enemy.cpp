#include "Enemy.h"

void Enemy::load(int x, int y, int width, int height, std::string textureID)
{
}

void Enemy::draw(SDL_Renderer* pRenderer)
{
    GameObject::draw(pRenderer);
}

void Enemy::update()
{
    m_y += 1;
    m_x += 1;
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Enemy::clean()
{
    GameObject::clean();
}
