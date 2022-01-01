#pragma once
#include <SFML/Graphics.hpp>
#include<memory>

enum class CursorPosition
{
    FirstPlayerType,
    SecondPlayerType,
    FirstPlayerUpControl,
    FirstPlayerDownControl,
    SecondPlayerUpControl,
    SecondPlayerDownControl,
};

class WorldSettings;

using Setting = std::pair<std::string, std::string*>;

class Menu
{
    sf::Text menuMessage;

    std::string firstPlayer;
    std::string secondPlayer;
    std::string firstPlayerControlUp;
    std::string firstPlayerControlDown;
    std::string secondPlayerControlUp;
    std::string secondPlayerControlDown;

    std::shared_ptr<WorldSettings> worldSettings;

    CursorPosition cursorPosition = CursorPosition::FirstPlayerType;
    std::vector<Setting> settings;
    bool isPressedChangeControl = false;

public:
    Menu();
    void setFont(const sf::Font& font);
    void draw(sf::RenderWindow& window);
    void setWorldSettings(std::shared_ptr<WorldSettings> _worldSettings);
    void handleEventKeyCode(sf::Keyboard::Key& code);
private:
    void onSettingsUpdate();
    void updateText();
    void updateMenuStringsFromSettings();
    void changePlayer();
    void changeControl(sf::Keyboard::Key& code);
    static bool isValidCodeForControl(sf::Keyboard::Key& code);
};
