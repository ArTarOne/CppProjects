#pragma once
#include <string>
#include <vector>

#include "GameState.h"

class GameObject;

class PauseState : public GameState
{
public:
    void        update() override;
    void        render() override;
    bool        onEnter() override;
    bool        onExit() override;
    std::string getStateID() const override;

private:
    static void              s_pauseToMain();
    static void              s_resumePlay();
    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;
};
