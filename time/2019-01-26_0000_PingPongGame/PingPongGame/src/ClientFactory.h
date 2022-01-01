#pragma once
#include <memory>
#include <string>
#include <vector>
#include "IClient.h"

enum class ClientType { Bot, User, Net };

class ClientFactory
{
public:
    std::shared_ptr<IClient> createClient(
        ClientType controllerType,
        std::vector<std::string>& params) const;
};
