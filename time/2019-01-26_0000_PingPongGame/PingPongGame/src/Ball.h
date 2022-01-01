#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Ball
{
    sf::CircleShape ballShape;
    sf::Sound ballSound;

public:
    Ball();
    void setPosition(const sf::Vector2f& position);
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow& window) const;
    void setRadius(float radius);
    void setSoundBuffer(const sf::SoundBuffer& ballSoundBuffer);
    void playSound();
};
