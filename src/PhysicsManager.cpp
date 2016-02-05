#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
: mEntities()
{
    //ctor
}

void PhysicsManager::registerEntity(Entity* entity)
{
    mEntities.push_back(entity);
}

void PhysicsManager::update(sf::Time dt)
{
    FOREACH(Entity* entity, mEntities)
    {
        sf::Vector2f positionA = entity->getPosition();
        FOREACH(Entity* entity, mEntities)
        {
            sf::Vector2f positionB = entity->getPosition();
            //sf::Vector2f distance = positionA - positionB;
            float diffY = positionA.y - positionB.y;
            float diffX = positionA.x - positionB.x;

            printf("%s", sqrt((diffY * diffY) + (diffX * diffX)) );
        }
    }
}



