#include "stdafx.h"
#include "Paddle.h"

Paddle::Paddle()
{
    const float lineThickness = 3;
    paddleShape.setOutlineThickness(lineThickness);
    paddleShape.setOutlineColor(sf::Color::Black);
    paddleShape.setFillColor(sf::Color(100, 100, 200));
}

void Paddle::setFillColor(const sf::Color& color)
{
    paddleShape.setFillColor(color);
}

void Paddle::setPosition(const sf::Vector2f& position)
{
    paddleShape.setPosition(position);
}

void Paddle::setPaddleSize(sf::Vector2f paddleSize)
{
    paddleShape.setSize(paddleSize);
    paddleShape.setOrigin(paddleSize / 2.f);
}

const sf::Vector2f& Paddle::getPosition() const
{
    return paddleShape.getPosition();
}

void Paddle::draw(sf::RenderWindow& window)
{
    window.draw(paddleShape);
}

void Paddle::move(const float offsetX, const float offsetY)
{
    paddleShape.move(offsetX, offsetY);
}

const sf::Vector2f& Paddle::getSize() const
{
    return paddleShape.getSize();
}
