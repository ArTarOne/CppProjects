﻿#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "GameState.h"

class MenuState : public GameState
{
public:
    void        update() override;
    void        render() override;
    bool        onEnter() override;
    bool        onExit() override;
    std::string getStateID() const override;

private:
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;

    // call back functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
};
