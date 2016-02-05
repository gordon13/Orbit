#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "SceneNode.h"
#include "CommandQueue.h"
#include <SFML/Graphics.hpp>
#include "Utility.h"
using namespace std;

class Entity : public SceneNode
{
    public:
        explicit        Entity(int hitpoints, int mass);

        void            setVelocity(sf::Vector2f velocity);
        void            setVelocity(float vx, float vy);
        void            setRotation(float rot);

        void			doRotate(float rot);

        void			accelerate(sf::Vector2f velocity);
		void			accelerate(float vx, float vy);

		void            repair(int points);
		void            damage(int points);
		void            destroy();
        int             getHitpoints() const;
        bool            isDestroyed() const;

        float           getRotation() const;
        sf::Vector2f    getVelocity() const;
        sf::Vector2f    getFullVelocity() const;

        //physics
        //void			addForce(sf::Vector2f force);
        //void			addForce(float fx, float fy);
        //sf::Vector2f	getForce();

    protected:
		virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);


    private:
        float           mRotation;
        sf::Vector2f    mVelocity;
        sf::Vector2f    mCurrentVel;
        //sf::Vector2f    mForce;
        int             mHitpoints;
        int             mMass;
};

#endif // ENTITY_H
