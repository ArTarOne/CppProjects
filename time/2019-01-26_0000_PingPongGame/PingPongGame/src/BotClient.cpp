#include "stdafx.h"
#include "BotClient.h"

void BotClient::setWorldState(const WorldState& ws)
{
    worldState = ws;
}

void BotClient::updateState()
{
    auto& ws = worldState;

    // Update the computer's paddle direction according to the ball position
    if(timer.getElapsedTime() > timerThreshold)
    {
        timer.restart();
        if(ws.ballCenter.y + ws.ballRadius >
           ws.rightPaddleCenter.y + ws.rightPaddleSize.y / 2)
            state = ClientState::PaddleDown;
        else if(ws.ballCenter.y - ws.ballRadius <
                ws.rightPaddleCenter.y - ws.rightPaddleSize.y / 2)
            state = ClientState::PaddleUp;
        else
            state = ClientState::None;
    }
}

ClientState BotClient::getClientState()
{
    return state;
}
