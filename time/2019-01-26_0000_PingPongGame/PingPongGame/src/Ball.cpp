#include "stdafx.h"
#include "Ball.h"

Ball::Ball()
{
    const float lineThickness = 5;
    ballShape.setOutlineThickness(lineThickness);
    ballShape.setOutlineColor(sf::Color::Black);
    ballShape.setFillColor(sf::Color::White);
}

void Ball::setPosition(const sf::Vector2f& position)
{
    ballShape.setPosition(position);
}

void Ball::move(const float offsetX, const float offsetY)
{
    ballShape.move(offsetX, offsetY);
}

void Ball::draw(sf::RenderWindow& window) const
{
    window.draw(ballShape);
}

void Ball::setRadius(float radius)
{
    ballShape.setRadius(radius);
    ballShape.setOrigin(radius / 2, radius / 2);
}

void Ball::setSoundBuffer(const sf::SoundBuffer& ballSoundBuffer)
{
    ballSound.setBuffer(ballSoundBuffer);
}

void Ball::playSound()
{
    ballSound.play();
}
