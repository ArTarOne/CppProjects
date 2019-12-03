#include "World.h"
#include "HelperFunctions.h"
#include <sstream>
#include "IBonusOwner.h"
#include "IDynamicObject.h"
#include <cassert>
#include "IDescructible.h"

std::vector<std::shared_ptr<IObject>> World::getAllObjects()
{
    std::vector<std::shared_ptr<IObject>> objects;
    objects.insert(objects.end(), m_balls.begin(), m_balls.end());
    objects.insert(objects.end(), m_plates.begin(), m_plates.end());
    objects.insert(objects.end(), m_bricks.begin(), m_bricks.end());
    objects.insert(objects.end(), m_walls.begin(), m_walls.end());
    objects.insert(objects.end(), m_bonuses.begin(), m_bonuses.end());
    return objects;
}

bool World::isObjectOutOfBorder(std::shared_ptr<IObject> object)
{
    auto objectPos = object->state().getPos();
    if (objectPos.x < 0 || objectPos.y < 0 ||
        objectPos.x > m_windowSize.x ||
        objectPos.y > m_windowSize.y)
    {
        return true;
    }

    return false;
}

World::World(std::shared_ptr<IObjectFactory> objectFactory, std::shared_ptr<ILevelGenerator> levelGenerator,
             sf::Vector2f windowSize)
{
    m_objectFactory = objectFactory;
    m_levelGenerator = levelGenerator;
    m_windowSize = windowSize;
    m_font = hf::getDefaultFont();
    m_isGameOver = true;
    m_scopes = 0;
}

void World::initCollisionProcessors()
{
    m_collisionBuckets.push_back({m_balls, m_walls, {}});
    m_collisionBuckets.push_back({m_balls, m_plates, {}});
    m_collisionBuckets.emplace_back(
        m_balls, m_bricks, [&](std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)
        {
            for (auto collision : collisions)
            {
                auto brickAsObject = collision.getObject();
                if (!brickAsObject->state().getDestroyFlag())
                    continue;
                auto object = m_objectFactory->createObject(ObjectType::Bonus);
                object->state().setSize({5, 5});
                object->state().setPos(thisObject->state().getPos());
                auto bonus = std::dynamic_pointer_cast<IBonusOwner>(object);
                auto brickAsBonusOwner = std::dynamic_pointer_cast<IBonusOwner>(collision.getObject());
                bonus->setBonusType(brickAsBonusOwner->getBonusType());
                m_bonuses.push_back(object);
            }
        }
    );
    m_collisionBuckets.push_back({m_plates, m_walls, {}});
    m_collisionBuckets.emplace_back(
        m_plates, m_bonuses, [&](std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)
        {
            for (auto& collision : collisions)
            {
                auto object = collision.getObject();
                object->state().setDestroyFlag(true);
                auto bonus = std::dynamic_pointer_cast<IBonusOwner>(object);
                auto plate = std::dynamic_pointer_cast<IBonusOwner>(thisObject);
                auto bonusType = bonus->getBonusType();
                plate->setBonusType(bonusType);
                if (bonusType && bonusType.value() == BonusType::MultiBalls)
                {

                    std::vector<std::shared_ptr<IObject>> createdBalls;
                    const unsigned maxNumberOfNewBalls = 2;
                    unsigned numberOfNewBalls = maxNumberOfNewBalls;
                    const float angleStep = 5;
                    float angleShift = 5;
                    while (!m_balls.empty() && numberOfNewBalls != 0)
                    {
                        assert(numberOfNewBalls <= maxNumberOfNewBalls);
                        for (auto existingBall : m_balls)
                        {
                            auto state = existingBall->state();
                            auto existingBallDynamicObject = std::dynamic_pointer_cast<IDynamicObject>(existingBall);
                            auto createdBall = m_objectFactory->createObject(ObjectType::Ball);
                            auto createdBallDynamicObject = std::dynamic_pointer_cast<IDynamicObject>(createdBall);
                            createdBall->state() = state;
                            auto speed = existingBallDynamicObject->getSpeed();
                            speed.rotate(angleShift);
                            createdBallDynamicObject->setSpeed(speed);
                            createdBalls.push_back(createdBall);
                            angleShift += angleStep;
                            if(angleShift == 0)
                                angleShift += angleStep;
                            numberOfNewBalls--;
                            if(numberOfNewBalls == 0)
                                break;
                        }
                    }
                    m_balls.insert(m_balls.end(), createdBalls.begin(), createdBalls.end());
                    unsigned maxNumberOfBalls = 10;
                    if(m_balls.size() > maxNumberOfBalls)
                    {
                        m_balls.resize(maxNumberOfBalls);                        
                    }

                }
                m_scopes++;
            }
        }
    );
}

void World::initPlates()
{
    float plateKoefThinkness = 0.04;
    float plateKoefSize = 0.2;
    auto plate = m_objectFactory->createObject(ObjectType::Plate);
    plate->state().setSize({m_windowSize.x * plateKoefSize, m_windowSize.y * plateKoefThinkness});
    plate->state().setPos({m_windowSize.x / 2, m_windowSize.y * (1 - plateKoefThinkness)});
    plate->setOnBumpingCallBack([&](auto, std::vector<Collision>& collisions)
    {
        m_scopes += collisions.size();
    });
    m_plates.push_back(plate);
}

void World::initWalls()
{
    float wallKoefThinkness = 0.02;
    float wallTopOffset = 0.05;
    sf::Vector2f verticalWallSize = {m_windowSize.x * wallKoefThinkness, m_windowSize.y * (1 - wallTopOffset)};
    auto leftWall = m_objectFactory->createObject(ObjectType::Wall);
    leftWall->state().setCollisionRect(verticalWallSize,
                                       {
                                           m_windowSize.x * wallKoefThinkness / 2,
                                           m_windowSize.y * (0.5f + wallTopOffset)
                                       });
    auto rightWall = m_objectFactory->createObject(ObjectType::Wall);
    rightWall->state().setCollisionRect(verticalWallSize,
                                        {
                                            m_windowSize.x * (1 - wallKoefThinkness / 2),
                                            m_windowSize.y * (0.5f + wallTopOffset)
                                        });
    sf::Vector2f horizontalWallSize = {m_windowSize.x, m_windowSize.y * wallKoefThinkness};
    auto topWall = m_objectFactory->createObject(ObjectType::Wall);
    topWall->state().setCollisionRect(horizontalWallSize,
                                      {m_windowSize.x / 2, m_windowSize.y * (wallKoefThinkness / 2 + wallTopOffset)});
    m_walls.push_back(leftWall);
    m_walls.push_back(rightWall);
    m_walls.push_back(topWall);
}

void World::initBricks()
{
    m_bricks = m_levelGenerator->getLevelBricks();
}

void World::initBalls()
{
    sf::Vector2f ballPos = {m_windowSize.x * 0.5f, m_windowSize.y * 0.9f};
    auto ball = m_objectFactory->createObject(ObjectType::Ball);
    ball->state().setPos(ballPos);
    m_balls.push_back(ball);
}

void World::generate()
{
    m_isGameOver = false;
    removeAllObjects();
    m_collisionBuckets.clear();

    initBalls();
    initBricks();
    initWalls();
    initPlates();
    initCollisionProcessors();
}

void World::removeObjectsIfDestroyed(std::vector<std::shared_ptr<IObject>>& objects)
{
    auto removeIt = std::remove_if(objects.begin(), objects.end(),
                                   [](std::shared_ptr<IObject> object)
                                   {
                                       return object->state().getDestroyFlag();
                                   });

    objects.erase(removeIt, objects.end());
}

void World::removeAllDestroyedObjects()
{
    removeObjectsIfDestroyed(m_balls);
    removeObjectsIfDestroyed(m_plates);
    removeObjectsIfDestroyed(m_bricks);
    removeObjectsIfDestroyed(m_walls);
    removeObjectsIfDestroyed(m_bonuses);
}

void World::removeAllObjects()
{
    m_balls.clear();
    m_plates.clear();
    m_bricks.clear();
    m_walls.clear();
    m_bonuses.clear();
}

void World::updateGameOverStatus()
{
    auto isAllBallsOutOfBorder = std::none_of(m_balls.begin(), m_balls.end(), [&](auto ball)
    {
        return !isObjectOutOfBorder(ball);
    });

    auto isAllBricksHaveSuperLive = std::all_of(m_bricks.begin(), m_bricks.end(), [&](auto brick)
        {
            auto destructibleBall = std::dynamic_pointer_cast<IDescructible>(brick);
            std::optional<int> lives = destructibleBall->getLives();
            return !lives.has_value();
        });

    if (isAllBallsOutOfBorder && !m_bricks.empty())
    {
        m_scopes = 0;
        m_isGameOver = true;
    }
    else if (m_bricks.empty() || isAllBricksHaveSuperLive)
    {
        std::for_each(m_balls.begin(), m_balls.end(), [](std::shared_ptr<IObject> ballObject)
        {
            ballObject->state().setDestroyFlag(true);
        });

        if (m_bonuses.empty())
            m_isGameOver = true;

        m_levelGenerator->changeLevel();
    }
}

void World::updateState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    m_elapsedTime_ms = elapsedTime.asMilliseconds();

    if (m_isGameOver)
    {
        generate();
    }

    for (auto& collisionProcessor : m_collisionBuckets)
    {
        collisionProcessor.process();
    }
    removeAllDestroyedObjects();

    for (auto object : getAllObjects())
    {
        object->calcState(event, elapsedTime);
        if (isObjectOutOfBorder(object))
        {
            object->state().setDestroyFlag(true);
        }
    }
    removeAllDestroyedObjects();

    updateGameOverStatus();
}

void World::draw(sf::RenderWindow& window)
{
    for (auto object : getAllObjects())
    {
        object->draw(window);
    }

    sf::Text text;
    text.setFont(m_font);
    text.setScale(0.7, 0.7);
    std::ostringstream ss;
    ss  << " Scopes: " << m_scopes
        << " Ball count: " << m_balls.size()
        << " Elapsed time: " << m_elapsedTime_ms << " ms"
        << std::endl;

    for (auto ball : m_balls)
    {
        ss << ball->state().getPos() << ", ";
    }

    text.setString(ss.str());
    window.draw(text);
}
