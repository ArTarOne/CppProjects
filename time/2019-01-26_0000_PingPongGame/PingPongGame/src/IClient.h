#pragma once

struct WorldState;

enum class ClientState { None, PaddleUp, PaddleDown };

class IClient
{
public:
    virtual ~IClient() = default;
    virtual void setWorldState(const WorldState&) = 0;
    virtual ClientState getClientState() = 0;
    virtual void updateState() = 0;
};
