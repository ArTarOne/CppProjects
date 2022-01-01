#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
    sf::RectangleShape paddleShape;

public:
    Paddle();
    void setFillColor(const sf::Color& color);
    void setPosition(const sf::Vector2f& position);
    void setPaddleSize(sf::Vector2f paddleSize);
    const sf::Vector2f& getPosition() const;
    void draw(sf::RenderWindow& window);
    void move(float offsetX, float offsetY);
    const sf::Vector2f& getSize() const;
};
