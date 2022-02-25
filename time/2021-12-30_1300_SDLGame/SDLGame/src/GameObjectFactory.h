#pragma once

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual             ~BaseCreator() = default;
};

class GameObjectFactory
{
public:
    static GameObjectFactory* instance();
    bool                      registerType(const std::string& typeID, BaseCreator* pCreator);
    GameObject*               create(const std::string& typeID);

private:
    GameObjectFactory();
    ~GameObjectFactory();

private:
    static GameObjectFactory*           s_pTheGameObjectFactory;
    std::map<std::string, BaseCreator*> m_creators;
};

using TheGameObjectFactory = GameObjectFactory;
