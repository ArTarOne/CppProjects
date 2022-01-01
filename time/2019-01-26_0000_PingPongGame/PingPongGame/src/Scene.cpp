#include "stdafx.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include "WorldSettings.h"

Scene::Scene()
{
    loadBallSoundBuffer();
    loadTextFont();

    leftPaddle.setFillColor(sf::Color(100, 100, 200));
    rightPaddle.setFillColor(sf::Color(200, 100, 100));

    menu.setFont(font);
}

void Scene::loadBallSoundBuffer()
{
    // Load the sounds used in the game
    const std::string soundFileName = "resources/ball.wav";
    if(!ballSoundBuffer.loadFromFile(soundFileName))
    {
        std::stringstream ss;
        ss << "can't load sound from file " << soundFileName;
        throw std::runtime_error(ss.str());
    }
    ball.setSoundBuffer(ballSoundBuffer);
}

void Scene::loadTextFont()
{
    // Load the text font
    const std::string fontFileName = "resources/sansation.ttf";
    if(!font.loadFromFile(fontFileName))
    {
        std::stringstream ss;
        ss << "can't load font from file " << fontFileName;
        throw std::runtime_error(ss.str());
    }
}

void Scene::draw(WorldState worldState)
{
    this->ws = worldState;
    drawEveryObject();
    window.display();
}

void Scene::drawEveryObject()
{
    leftPaddle.setPaddleSize(ws.leftPaddleSize);
    leftPaddle.setPosition(ws.leftPaddleCenter);
    rightPaddle.setPaddleSize(ws.rightPaddleSize);
    rightPaddle.setPosition(ws.rightPaddleCenter);
    ball.setRadius(ws.ballRadius);
    ball.setPosition(ws.ballCenter);

    window.clear(sf::Color(50, 200, 50));

    if(ws.isPlaying)
    {
        leftPaddle.draw(window);
        rightPaddle.draw(window);
        ball.draw(window);
        if(ws.isBallCollision)
            ball.playSound();
    }
    else
    {
        menu.setWorldSettings(worldSettings);
        menu.draw(window);
    }
}

void Scene::onSettingsUpdate()
{
    window.create(sf::VideoMode(worldSettings->width,
                                worldSettings->height,
                                32),
                  worldSettings->title,
                  sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
}

bool Scene::pollEvent(sf::Event& event)
{
    return window.pollEvent(event);
}

void Scene::close()
{
    window.close();
}

bool Scene::isOpen() const
{
    return window.isOpen();
}

void Scene::setWorldSettings(std::shared_ptr<WorldSettings> _worldSettings)
{
    worldSettings = _worldSettings;
    std::function<void()> cb = std::bind(&Scene::onSettingsUpdate, this);
    worldSettings->subscribe(cb);
}

void Scene::handleEvent(sf::Event& event)
{
    menu.handleEventKeyCode(event.key.code);
}
