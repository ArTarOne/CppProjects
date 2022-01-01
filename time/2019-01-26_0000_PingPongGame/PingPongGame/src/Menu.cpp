#include "stdafx.h"
#include <functional>
#include "Menu.h"
#include "WorldSettings.h"

std::string getStringFromKey(const sf::Keyboard::Key control)
{
    auto SFControlsVec = Helper::getSMFLControlKeys();
    return SFControlsVec[control];
}

Menu::Menu()
{
    settings =
    {
        { "First player", &firstPlayer },
        { "Second player", &secondPlayer },
        { "First player control up", &firstPlayerControlUp },
        { "First player control down", &firstPlayerControlDown },
        { "Second player control up", &secondPlayerControlUp },
        { "Second player control down", &secondPlayerControlDown },
    };
}

void Menu::setFont(const sf::Font& font)
{
    menuMessage.setFont(font);
}

void Menu::draw(sf::RenderWindow& window)
{
    updateText();
    window.draw(menuMessage);
}

void Menu::onSettingsUpdate()
{
    updateText();
}

void Menu::setWorldSettings(std::shared_ptr<WorldSettings> _worldSettings)
{
    worldSettings = _worldSettings;
    std::function<void()> cb = std::bind(&Menu::onSettingsUpdate, this);
    worldSettings->subscribe(cb);
}

void Menu::updateText()
{
    updateMenuStringsFromSettings();

    std::ostringstream os;
    os.str("");
    os << "Welcome to SFML pong!\n"
        << "Press space to start the game\n"
        << "Use the arrow keys to change the values\n"
        << "For change control press enter and set new control\n"
        << "You can choose letters, numbers, arrows and numpad .\n\n";

    for(unsigned i = 0; i < settings.size(); ++i)
    {
        const CursorPosition currentPosition = static_cast<CursorPosition>(i);
        if(currentPosition == cursorPosition)
        {
            os << ">>  ";
        }
        else
        {
            os << "    ";
        }

        os << settings[i].first << ":  ";

        if(currentPosition == cursorPosition && isPressedChangeControl)
        {
            os << "< PRESS ANY KEY >";
        }
        else
        {
            os << *(settings[i].second);
        }

        os << "\n";
    }

    menuMessage.setString(os.str());
}

void Menu::updateMenuStringsFromSettings()
{
    firstPlayer = worldSettings->
        convertFromClientTypeToString(worldSettings->firstClientType);
    secondPlayer = worldSettings->
        convertFromClientTypeToString(worldSettings->secondClientType);
    firstPlayerControlUp = worldSettings->firstPlayerControl[0];
    firstPlayerControlDown = worldSettings->firstPlayerControl[1];
    secondPlayerControlUp = worldSettings->secondPlayerControl[0];
    secondPlayerControlDown = worldSettings->secondPlayerControl[1];
}

void Menu::handleEventKeyCode(sf::Keyboard::Key& code)
{
    switch(code)
    {
    case sf::Keyboard::Enter:
        isPressedChangeControl = true;
        break;
    case sf::Keyboard::Down:
        if(isPressedChangeControl &&
           (cursorPosition == CursorPosition::FirstPlayerUpControl || 
               cursorPosition == CursorPosition::FirstPlayerDownControl ||
               cursorPosition == CursorPosition::SecondPlayerUpControl || 
               cursorPosition == CursorPosition::SecondPlayerDownControl))
        {
            changeControl(code);
            worldSettings->save();
            isPressedChangeControl = false;
        }
        else
        {
            cursorPosition = static_cast<CursorPosition>(
                (static_cast<unsigned>(cursorPosition) + 1) % settings.size());
            isPressedChangeControl = false;
        }
        break;
    case sf::Keyboard::Up:
        if(isPressedChangeControl &&
           (cursorPosition == CursorPosition::FirstPlayerUpControl || 
               cursorPosition == CursorPosition::FirstPlayerDownControl ||
               cursorPosition == CursorPosition::SecondPlayerUpControl || 
               cursorPosition == CursorPosition::SecondPlayerDownControl))
        {
            changeControl(code);
            worldSettings->save();
            isPressedChangeControl = false;
        }
        else
        {
            cursorPosition = static_cast<CursorPosition>(
                (static_cast<unsigned>(cursorPosition) - 1) % settings.size());
            isPressedChangeControl = false;
        }
        break;
    case sf::Keyboard::Right:
        if(cursorPosition == CursorPosition::FirstPlayerType || 
            cursorPosition == CursorPosition::SecondPlayerType)
        {
            changePlayer();
            isPressedChangeControl = false;
        }
        break;
    case sf::Keyboard::Left:
        if(cursorPosition == CursorPosition::FirstPlayerType || 
            cursorPosition == CursorPosition::SecondPlayerType)
        {
            changePlayer();
            isPressedChangeControl = false;
        }
        break;
    default:
        if(isPressedChangeControl &&
           (cursorPosition == CursorPosition::FirstPlayerUpControl || 
               cursorPosition == CursorPosition::FirstPlayerDownControl ||
               cursorPosition == CursorPosition::SecondPlayerUpControl || 
               cursorPosition == CursorPosition::SecondPlayerDownControl))
        {
            changeControl(code);
            worldSettings->save();
            isPressedChangeControl = false;
        }
        break;
    }
    updateText();
}

void Menu::changePlayer()
{
    switch(cursorPosition)
    {
    case CursorPosition::FirstPlayerType:
        if(firstPlayer == "Bot")
            worldSettings->firstClientType = ClientType::User;
        else if(firstPlayer == "User")
            worldSettings->firstClientType = ClientType::Bot;
        break;
    case CursorPosition::SecondPlayerType:
        if(secondPlayer == "Bot")
            worldSettings->secondClientType = ClientType::User;
        else if(secondPlayer == "User")
            worldSettings->secondClientType = ClientType::Bot;
        break;
    default:
        break;
    }

    worldSettings->save();
}

void Menu::changeControl(sf::Keyboard::Key& code)
{
    switch(cursorPosition)
    {
    case CursorPosition::FirstPlayerUpControl:
        if(isValidCodeForControl(code))
            worldSettings->firstPlayerControl[0] = getStringFromKey(code);
        break;
    case CursorPosition::FirstPlayerDownControl:
        if(isValidCodeForControl(code))
            worldSettings->firstPlayerControl[1] = getStringFromKey(code);
        break;
    case CursorPosition::SecondPlayerUpControl:
        if(isValidCodeForControl(code))
            worldSettings->secondPlayerControl[0] = getStringFromKey(code);
        break;
    case CursorPosition::SecondPlayerDownControl:
        if(isValidCodeForControl(code))
            worldSettings->secondPlayerControl[1] = getStringFromKey(code);
        break;
    default:
        break;
    }
}

bool Menu::isValidCodeForControl(sf::Keyboard::Key& code)
{
    if((code > -1 && code < 36) || (code > 70 && code < 85))
    {
        return true;
    }
    return false;
}
