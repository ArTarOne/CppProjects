#pragma once
#include <vector>

#include "MenuState.h"

class GameObject;

class GameOverState : public MenuState
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
    static void s_gameOverToMain();
    static void s_restartPlay();

private:
    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;
};
