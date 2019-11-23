#include "World.h"
#include "HelperFunctions.h"

std::vector<std::shared_ptr<IObject>> World::getAllObjects()
{
    std::vector<std::shared_ptr<IObject>> allObjects;
    auto mainObjects = getPrimaryObjects();
    auto noMainObjects = getSecondaryObjects();
    allObjects.insert(allObjects.end(), mainObjects.begin(), mainObjects.end());
    allObjects.insert(allObjects.end(), noMainObjects.begin(), noMainObjects.end());
    return allObjects;
}

std::vector<std::shared_ptr<IObject>> World::getPrimaryObjects()
{
    std::vector<std::shared_ptr<IObject>> objects;
    objects.insert(objects.end(), m_balls.begin(), m_balls.end());
    objects.insert(objects.end(), m_plates.begin(), m_plates.end());
    return objects;
}

std::vector<std::shared_ptr<IObject>> World::getSecondaryObjects()
{
    std::vector<std::shared_ptr<IObject>> objects;
    objects.insert(objects.end(), m_matrix.begin(), m_matrix.end());
    objects.insert(objects.end(), m_walls.begin(), m_walls.end());
    objects.insert(objects.end(), m_bonuses.begin(), m_bonuses.end());
    return objects;
}

bool World::isObjectOutOfBorder(std::shared_ptr<IObject> object)
{
    auto objectPos = object->getState().getPos();
    if (objectPos.x < 0 || objectPos.y < 0 ||
        objectPos.x > m_worldSize.x ||
        objectPos.y > m_worldSize.y)
    {
        return true;
    }

    return false;
}

World::World(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize)
{
    m_worldSize = worldSize;
    m_objectFactory = objectFactory;
}

void World::generate()
{
}

bool World::isGameOver()
{
}

void World::removeObjectsIfDestroyed(std::vector<std::shared_ptr<IObject>>& objects)
{
    auto removeIt = std::remove_if(objects.begin(), objects.end(),
                                   [](std::shared_ptr<IObject> object)
                                   {
                                       return object->state().getIsDestroyed();
                                   });

    objects.erase(removeIt, objects.end());
}

void World::removeAllDestroyedObjects()
{
    removeObjectsIfDestroyed(m_balls);
    removeObjectsIfDestroyed(m_plates);
    removeObjectsIfDestroyed(m_matrix);
    removeObjectsIfDestroyed(m_walls);
    removeObjectsIfDestroyed(m_bonuses);
}

void World::updateState(sf::Event event, sf::Time timeStep)
{
    auto allObjects = getAllObjects();
    for (auto object : allObjects)
    {
        object->calcState(event, timeStep);
        if (isObjectOutOfBorder(object))
        {
            object->state().setIsDestroyed(true);
        }
    }
    removeAllDestroyedObjects();

    for (auto primaryObject : getPrimaryObjects())
    {
        for (auto secondaryObject : getSecondaryObjects())
        {
            // TODO
        }        
    }
}

void World::draw(sf::RenderWindow& window)
{
}
