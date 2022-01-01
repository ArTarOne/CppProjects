#pragma once
#include <memory>
#include "Paddle.h"
#include "Ball.h"
#include "Menu.h"
#include "WorldState.h"

class WorldSettings;

class Scene
{
    WorldState ws {};
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    sf::SoundBuffer ballSoundBuffer;
    sf::Font font;
    Menu menu;
    sf::RenderWindow window;
    std::shared_ptr<WorldSettings> worldSettings;

public:
    Scene();
    void setWorldSettings(std::shared_ptr<WorldSettings> _worldSettings);
    void draw(WorldState worldState);
    bool pollEvent(sf::Event& event);
    bool isOpen() const;
    void close();

    void handleEvent(sf::Event& event);

private:
    void loadBallSoundBuffer();
    void loadTextFont();
    void drawEveryObject();
    void onSettingsUpdate();
};
