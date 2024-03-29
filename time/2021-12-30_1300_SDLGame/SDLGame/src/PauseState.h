﻿#pragma once
#include <string>
#include <vector>

#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:
    void        update() override;
    void        render() override;
    bool        onEnter() override;
    bool        onExit() override;
    std::string getStateID() const override;

protected:
    void setCallbacks(const std::vector<Callback>& callbacks) override;

private:
    static void s_pauseToMain();
    static void s_resumePlay();

private:
    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;
};
