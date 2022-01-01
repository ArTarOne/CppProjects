#include "stdafx.h"
#include "WorldSettings.h"

void WorldSettings::load()
{
    if(!settingsParser.loadFromFile("resources/settings.txt"))
    {
        throw std::logic_error("Error loading settings file!");
    }

    settingsParser.get("width", width);
    settingsParser.get("height", height);

    std::string firstPlayerStr = "User";
    settingsParser.get("FirstPlayer", firstPlayerStr);
    settingsParser.get("FirstPlayerControlKeys", firstPlayerControlKeys);
    std::string secondPlayerStr = "Bot";
    settingsParser.get("SecondPlayer", secondPlayerStr);
    settingsParser.get("SecondPlayerControlKeys", secondPlayerControlKeys);

    firstPlayerControl = parseControlKeys(firstPlayerControlKeys);
    secondPlayerControl = parseControlKeys(secondPlayerControlKeys);

    if(firstPlayerStr == "User")
        firstClientType = ClientType::User;
    else if(firstPlayerStr == "Bot")
        firstClientType = ClientType::Bot;
    else
        throw std::logic_error("Unknown string of FirstPlayer");

    if(secondPlayerStr == "User")
        secondClientType = ClientType::User;
    else if(secondPlayerStr == "Bot")
        secondClientType = ClientType::Bot;
    else
        throw std::logic_error("Unknown string of SecondPlayer");

    settingsParser.print();

    for(auto& cb : callbacks)
    {
        cb();
    }
}

void WorldSettings::save()
{
    for(auto& cb : callbacks)
    {
        cb();
    }

    if(firstClientType == ClientType::User)
        settingsParser.set("FirstPlayer", "User");
    else if(firstClientType == ClientType::Bot)
        settingsParser.set("FirstPlayer", "Bot");
    else if(firstClientType == ClientType::Net)
        settingsParser.set("FirstPlayer", "Net");
    else
        throw std::logic_error("Error no Player 1 chosen!");

    if(secondClientType == ClientType::User)
        settingsParser.set("SecondPlayer", "User");
    else if(secondClientType == ClientType::Bot)
        settingsParser.set("SecondPlayer", "Bot");
    else if(secondClientType == ClientType::Net)
        settingsParser.set("SecondPlayer", "Net");
    else
        throw std::logic_error("Error no Player 2 chosen!");

    settingsParser.set("FirstPlayerControlKeys",
                       firstPlayerControl[0] + "," + firstPlayerControl[1]);
    settingsParser.set("SecondPlayerControlKeys",
                       secondPlayerControl[0] + "," + secondPlayerControl[1]);

    settingsParser.saveToFile();
}

void WorldSettings::subscribe(std::function<void()> cb)
{
    callbacks.push_back(cb);
}

std::vector<std::string> WorldSettings::parseControlKeys(
    const std::string& controlKeys)
{
    std::vector<std::string> keys;

    auto splitPos = controlKeys.find(',');

    std::string key = controlKeys.substr(0, splitPos);
    keys.push_back(key);

    key = controlKeys.substr(splitPos + 1, controlKeys.size() - 1);
    keys.push_back(key);

    return keys;
}

std::string WorldSettings::convertFromClientTypeToString(ClientType clientType)
{
    switch(clientType)
    {
    case ClientType::User:
        return "User";
    case ClientType::Bot:
        return "Bot";
    case ClientType::Net:
        return "Net";
    default:
        throw std::logic_error("error: unknown ClientType");
    }
}
