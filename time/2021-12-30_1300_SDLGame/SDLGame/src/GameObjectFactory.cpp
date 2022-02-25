#include <iostream>

#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_pTheGameObjectFactory = nullptr;

GameObjectFactory::GameObjectFactory() = default;

GameObjectFactory::~GameObjectFactory() = default;

GameObjectFactory* GameObjectFactory::instance()
{
    if(s_pTheGameObjectFactory == nullptr)
    {
        s_pTheGameObjectFactory = new GameObjectFactory();
        return s_pTheGameObjectFactory;
    }
    return s_pTheGameObjectFactory;
}

bool GameObjectFactory::registerType(const std::string& typeID, BaseCreator* pCreator)
{
    const auto& it = m_creators.find(typeID);
    // if the type is already registered, do nothing
    if(it != m_creators.end())
    {
        delete pCreator;
        return false;
    }
    m_creators[typeID] = pCreator;
    return true;
}

GameObject* GameObjectFactory::create(const std::string& typeID)
{
    const auto& it = m_creators.find(typeID);
    if(it == m_creators.end())
    {
        std::cerr << "could not find type: " << typeID << "\n";
        return nullptr;
    }
    const BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}
