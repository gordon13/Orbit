#include "Entity.h"
#include <cassert>

Entity::Entity(int hitpoints, int mass)
: mVelocity()
, mCurrentVel()
, mMass(mass)
, mHitpoints(hitpoints)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    //mVelocity = velocity;
    mCurrentVel = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mCurrentVel.x = vx;
    mCurrentVel.y = vy;
    //mVelocity.x = vx;
    //mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mCurrentVel;
    //return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mCurrentVel += mVelocity + velocity;
}

void Entity::accelerate(float vx, float vy)
{
	sf::Vector2f v(vx, vy);
	mCurrentVel += mVelocity + v;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
    move(mCurrentVel * dt.asSeconds());
}


void Entity::repair(int points)
{
    assert(points > 0);
    mHitpoints += points;
}

void Entity::damage(int points)
{
    assert(points > 0);
    mHitpoints -= points;
}

void Entity::destroy()
{
    mHitpoints = 0;
}

bool Entity::isDestroyed() const
{
    return mHitpoints <= 0;
}

int Entity::getHitpoints() const
{
    return mHitpoints;
}







