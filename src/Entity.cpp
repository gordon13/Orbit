#include "Entity.h"
#include <cassert>

Entity::Entity(int hitpoints, int mass)
: mVelocity()
, mRotation()
, mCurrentVel()
, mMass(mass)
, mHitpoints(hitpoints)
{
}

float Entity::getMass() const
{
    return mMass;
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

void Entity::setRotation(float rot)
{
    mRotation = rot;
}

void Entity::doRotate(float rot)
{
    //printf("Rot: %f \n",rot);
    mRotation += rot;
}

sf::Vector2f Entity::getVelocity() const
{
    return mCurrentVel;
    //return mVelocity;
}

float Entity::getRotation() const
{
    return mRotation;
}

float Entity::getOrientation() const
{
    return this->Transformable::getRotation() + 90;
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

void Entity::accelerateTowards(float thrust, float angle)
{
    //ship.accelerate(cos(rotateVelocity) * getMaxThrust(), sin(rotateVelocity) * getMaxThrust());
    //printf("%f \n",angle);
	sf::Vector2f v(cos(angle*PI/180) * thrust, sin(angle*PI/180) * thrust);
	mCurrentVel += mVelocity + v;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
    rotate(mRotation * dt.asSeconds());
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







