#pragma once
#include "IClient.h"

class ProxyClient : public IClient
{
public:
    void setWorldState(const WorldState&) override;
    bool paddleUp() const;
    bool paddleDown() const;
    void updateState() override;
};
