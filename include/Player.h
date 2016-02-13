#ifndef PLAYER_H
#define PLAYER_H

#include "CommandQueue.h"
#include "Command.h"

#include <SFML/Window/Event.hpp>

#include <map>
#include <math.h>

class CommandQueue;

class Player
{
    public:
		enum Action
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			ActionCount
		};

    public:
        Player();
        void                handleEvent(const sf::Event& event,
                                        CommandQueue& commands);
        void                handleRealtimeInput(CommandQueue& commands);

        void                assignKey(Action action,
                                        sf::Keyboard::Key key);
        sf::Keyboard::Key   getAssignedKey(Action action) const;

    private:
		void					initializeActions();
		static bool				isRealtimeAction(Action action);

    private:
        float                                   playerSpeed;
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;

};

#endif // PLAYER_H
