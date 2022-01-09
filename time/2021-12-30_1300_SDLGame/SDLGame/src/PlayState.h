#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "GameState.h"

class SDLGameObject;

class PlayState : public GameState
{
public:
    void        update() override;
    void        render() override;
    bool        onEnter() override;
    bool        onExit() override;
    std::string getStateID() const override;
    bool        checkCollision(SDLGameObject* p1, SDLGameObject* p2);

private:
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};
