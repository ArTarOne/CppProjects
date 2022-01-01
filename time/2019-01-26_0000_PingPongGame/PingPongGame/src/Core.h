#pragma once
#include "WorldState.h"
#include "Menu.h"
#include "ClientFactory.h"

class WorldSettings;

class Core
{
    WorldState worldState {};
    float ballAngle = 0.f; // to be changed later
    sf::Clock clock;
    std::shared_ptr<IClient> client01;
    std::shared_ptr<IClient> client02;
    ClientFactory clientFactory;
    std::shared_ptr<WorldSettings> worldSettings;

public:
    Core() = default;
    void restartGame();
    void iterate();
    void setWorldSettings(std::shared_ptr<WorldSettings> _worldSettings);
    WorldState getUpdatedWorldState() const;

private:
    bool checkAllCollision();
    bool checkPaddlesCollision();
    bool checkScreenCollision();
    void movePaddles(float);
    void moveBall(float);
    void correctPaddlePosition(sf::Vector2f& paddlePos,
                               sf::Vector2f& paddleSize);
    void onSettingsUpdate();
    void createClients();
};
