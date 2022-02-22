#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "GameState.h"
#include "LevelParser.h"

class SDLGameObject;

class PlayState : public GameState
{
public:
    PlayState();

    void        update() override;
    void        render() override;
    bool        onEnter() override;
    bool        onExit() override;
    std::string getStateID() const override;

private:
    static const std::string s_playID;
    Level*                   m_pLevel;
};
