#pragma once
#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();

    void update();
    void render();
    void destroyRemoveCandidates();

private:
    std::vector<GameState*> m_gameStates;
    std::vector<GameState*> m_removeCandidates;
};
