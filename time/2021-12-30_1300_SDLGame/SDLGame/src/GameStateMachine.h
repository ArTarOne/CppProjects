#pragma once
#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();

private:
    std::vector<GameState*> m_gameStates;
};
