#include "stdafx.h"
#include "ClientFactory.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <cctype>
#include "KeyboardClient.h"
#include "BotClient.h"
#include <SFML/Network.hpp>

sf::Keyboard::Key getKeyFromChar(char letter)
{
    letter = std::toupper(letter);
    const auto offset = 'A';
    return static_cast<sf::Keyboard::Key>(letter - offset);
}

sf::Keyboard::Key getKeyFromString(const std::string& control)
{
    auto SFControlsVec = Helper::getSMFLControlKeys();

    for(unsigned i = 0; i < SFControlsVec.size(); ++i)
    {
        if(SFControlsVec[i] == control)
            return static_cast<sf::Keyboard::Key>(i);
    }

    throw std::logic_error("error: set unknown  controls ");
}

std::shared_ptr<IClient> ClientFactory::createClient(
    const ClientType controllerType,
    std::vector<std::string>& params) const
{
    switch(controllerType)
    {
    case ClientType::User:
        assert(!params.empty());
        return std::static_pointer_cast<IClient>(
            std::make_shared<KeyboardClient>(
                getKeyFromString(params[0]),
                getKeyFromString(params[1])));
    case ClientType::Bot:
        return std::static_pointer_cast<IClient>(std::make_shared<BotClient>());
    case ClientType::Net:
        throw std::logic_error("Net Type isn't implemented");
    }

    return {};
}
