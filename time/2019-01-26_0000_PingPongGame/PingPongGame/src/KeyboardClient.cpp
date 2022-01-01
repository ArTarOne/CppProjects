#include "stdafx.h"
#include "KeyboardClient.h"
#include <SFML/Window/Keyboard.hpp>

KeyboardClient::KeyboardClient(const sf::Keyboard::Key up,
                               const sf::Keyboard::Key down)
{
    this->up = up;
    this->down = down;
}

void KeyboardClient::updateState()
{
    // do nothing
}

void KeyboardClient::setWorldState(const WorldState&)
{
    // do nothing
}

ClientState KeyboardClient::getClientState()
{
    if(sf::Keyboard::isKeyPressed(up))
        return ClientState::PaddleUp;

    if(sf::Keyboard::isKeyPressed(down))
        return ClientState::PaddleDown;

    return ClientState::None;
}
