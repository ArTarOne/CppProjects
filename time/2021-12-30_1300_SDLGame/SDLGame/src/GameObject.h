#pragma once

#include "LoaderParams.h"

class GameObject
{
public:
    virtual ~GameObject() = default;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;    
};
