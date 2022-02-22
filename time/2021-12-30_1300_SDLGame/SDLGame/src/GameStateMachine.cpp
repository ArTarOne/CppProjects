#include <iostream>

#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState)
{
    if(!m_gameStates.empty() && m_gameStates.back()->getStateID() == pState->getStateID())
    {
        return;
    }

    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState)
{
    _ASSERT(pState);

    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }

        if(m_gameStates.back()->onExit())
        {
            m_removeCandidates.push_back(m_gameStates.back());
            m_gameStates.pop_back();
        }
    }

    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
    if(m_gameStates.empty())
    {
        return;
    }

    if(m_gameStates.back()->onExit())
    {
        m_removeCandidates.push_back(m_gameStates.back());
        m_gameStates.pop_back();
    }
}

void GameStateMachine::update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->render();
    }
}

void GameStateMachine::destroyRemoveCandidates()
{
    for(auto& stateToDelete : m_removeCandidates)
    {
        delete stateToDelete;
    }
    m_removeCandidates.clear();
}
