#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "Entity.h"
#include "foreach.h"
#include <SFML/System/Vector2.hpp>

class PhysicsManager
{
    public:
                        PhysicsManager();
        void                    registerEntity(Entity* entity);
        void                    update(sf::Time dt);

    private:
        std::vector<Entity*>	    mEntities;
        //std::vector<State::Ptr>                 mStack;
};

#endif // PHYSICSMANAGER_H
