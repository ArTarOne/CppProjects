#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "../src/ClientFactory.h"

class KeyboardClient : public IClient
{
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;

public:
    KeyboardClient(sf::Keyboard::Key up, sf::Keyboard::Key down);
    void updateState() override;
    void setWorldState(const WorldState&) override;
    ClientState getClientState() override;
};
