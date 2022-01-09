#pragma once
#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic(const LoaderParams* pParams, int animSpeed);
    ~AnimatedGraphic() override;

    void draw() override;
    void update() override;
    void clean() override;

private:
    int m_animSpeed;
};
