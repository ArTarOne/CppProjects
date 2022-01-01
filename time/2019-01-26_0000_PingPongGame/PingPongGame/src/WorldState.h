#pragma once
#include <SFML/System/Vector2.hpp>

struct WorldState
{
    sf::Vector2i screenSize;
    sf::Vector2f leftPaddleSize = { 25, 100 };
    sf::Vector2f leftPaddleCenter;
    sf::Vector2f rightPaddleSize = { 25, 100 };
    sf::Vector2f rightPaddleCenter;
    sf::Vector2f ballCenter;
    float ballRadius = 10.f;
    float paddleSpeed = 400.f;
    float ballSpeed = 400.f;
    bool isBallCollision = false;
    bool isPlaying = false;

    // TODO refactor it later
    void moveLeftPaddle(float x, float y)
    {
        leftPaddleCenter.x += x;
        leftPaddleCenter.y += y;
    }

    // TODO refactor it later
    void moveRightPaddle(float x, float y)
    {
        rightPaddleCenter.x += x;
        rightPaddleCenter.y += y;
    }

    // TODO refactor it later
    void moveBall(float x, float y)
    {
        ballCenter.x += x;
        ballCenter.y += y;
    }
};
