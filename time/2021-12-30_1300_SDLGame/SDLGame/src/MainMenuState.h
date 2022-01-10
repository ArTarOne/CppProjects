#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
    MainMenuState();
    ~MainMenuState() override;

    void        update() override;
    void        render() override;
    bool        onEnter() override;
    bool        onExit() override;
    std::string getStateID() const override;

private:
    void setCallbacks(const std::vector<Callback>& callbacks) override;

    // call back functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();

private:
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};
