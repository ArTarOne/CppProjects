#pragma once
#include <vector>

#include "GameState.h"

class GameObject;

class GameOverState : public GameState
{
public:
    void        update() override;
    void        render() override;
    bool        onEnter() override;
    bool        onExit() override;
    std::string getStateID() const override;

private:
    static void              s_gameOverToMain();
    static void              s_restartPlay();
    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;
};
