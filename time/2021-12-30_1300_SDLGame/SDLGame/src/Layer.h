﻿#pragma once

class Layer
{
public:
    virtual void render() = 0;
    virtual void update() = 0;

    virtual ~Layer() = default;
};
