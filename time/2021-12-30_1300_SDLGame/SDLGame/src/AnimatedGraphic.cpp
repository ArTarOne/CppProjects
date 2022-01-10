#include <SDL2/SDL_timer.h>

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() = default;

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
    m_currentFrame = static_cast<int>((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames);
}

void AnimatedGraphic::clean()
{
    SDLGameObject::clean();
}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
}

GameObject* AnimatedGraphicCreator::createGameObject() const
{
    return new AnimatedGraphic();
}
