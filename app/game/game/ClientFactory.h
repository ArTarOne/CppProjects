#pragma once
#include <memory>

struct ServerPackage;

class IClient
{
public:
    virtual ~IClient() = default;
    virtual void setServerPackage(const ServerPackage & serverPackage) {}
    virtual bool paddleUp() const = 0;
    virtual bool paddleDown() const = 0;
    virtual void updateState() = 0;
};

enum class ClientType { Bot, User };


class ClientFactory
{   

public:
    std::shared_ptr<IClient> createClient(ClientType controllerType);
};