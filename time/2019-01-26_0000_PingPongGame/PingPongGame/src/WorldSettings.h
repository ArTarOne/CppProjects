#pragma once
#include "SettingsParser.hpp"
#include "ClientFactory.h"
#include <functional>
#include <vector>

class WorldSettings
{
    SettingsParser settingsParser;
    std::vector<std::function<void()>> callbacks;

public:
    int width = 800;
    int height = 600;
    std::string title = "Ping Pong";
    std::string firstPlayerControlKeys = "W,S";
    std::string secondPlayerControlKeys = "P,L";
    ClientType firstClientType = ClientType::User;
    ClientType secondClientType = ClientType::Bot;

    std::vector<std::string> firstPlayerControl;
    std::vector<std::string> secondPlayerControl;
    static std::vector<std::string> parseControlKeys(
        const std::string& controlKeys);

    void load();
    void save();
    void subscribe(std::function<void()> cb);

    static std::string convertFromClientTypeToString(ClientType clientType);
};
