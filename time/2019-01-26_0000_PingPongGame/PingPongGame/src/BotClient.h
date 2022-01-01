#pragma once
#include "ClientFactory.h"
#include <SFML/System/Clock.hpp>
#include "WorldState.h"

class BotClient : public IClient
{
    WorldState worldState {};
    float rightPaddleSpeed = 0.f;
    ClientState state = ClientState::None;
    sf::Clock timer;
    const sf::Time timerThreshold = sf::seconds(0.1f);

public:
    void setWorldState(const WorldState& ws) override;
    void updateState() override;
    ClientState getClientState() override;
};
