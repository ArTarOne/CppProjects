#include <iostream>

#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;

GameObjectFactory::GameObjectFactory() = default;

GameObjectFactory::~GameObjectFactory() = default;

GameObjectFactory* GameObjectFactory::Instance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new GameObjectFactory();
        return s_pInstance;
    }
    return s_pInstance;
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
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
        std::cout << "could not find type: " << typeID << "\n";
        return nullptr;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}
