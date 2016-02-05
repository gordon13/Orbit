#include "Player.h"
#include "CommandQueue.h"
#include "Ship.h"
#include "foreach.h"
#include "Utility.h"
#include <iostream>

struct ShipMover
{
    ShipMover(float vx, float vy)
    : rotateVelocity(vx)
    , input(vx, vy)
    , velocity(vx, vy)
    {
    }

    void operator() (Ship& ship, sf::Time) const
    {

        printf( "Rotation: %s RotateVel: %s MaxVel: %s MaxThrust %s \n", toString(ship.getRotation()).c_str(), toString(rotateVelocity).c_str(), toString(ship.getMaxRotateVelocity()).c_str(), toString(ship.getMaxThrust()).c_str() );
        ship.accelerate(velocity * ship.getMaxThrust());
        ship.doRotate(rotateVelocity * ship.getMaxRotateVelocity());
    }
    sf::Vector2f input;
    sf::Vector2f velocity;
    float rotateVelocity;
};

Player::Player()
{

	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

    initializeActions();

	// Assign all categories to player's aircraft
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerShip;
}


void Player::handleRealtimeInput(CommandQueue& commands)
{
    FOREACH(auto pair, mKeyBinding)
    {
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
            commands.push(mActionBinding[pair.second]);
    }
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{

	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}


void Player::initializeActions()
{
	mActionBinding[MoveLeft].action	 = derivedAction<Ship>(ShipMover(-1, 0));
	mActionBinding[MoveRight].action = derivedAction<Ship>(ShipMover(1, 0));
	mActionBinding[MoveUp].action    = derivedAction<Ship>(ShipMover(0, -1));
	mActionBinding[MoveDown].action  = derivedAction<Ship>(ShipMover(0, 1));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
		case MoveUp:
		    return true;

		default:
			return false;
	}
}
