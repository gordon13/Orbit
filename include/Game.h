#ifndef GAME_H
#define GAME_H

#include <World.h>
#include <Player.h>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable
{
    public:
        Game();
        void run();

    private:
        //void processEvents();
        void processInput();
        void update(sf::Time elapsedTime);
        void render();

        //void handlePlayerInput(sf::Keyboard::Key key,
         //                      bool isPressed);

    private:
        static const sf::Time	TimePerFrame;

        sf::RenderWindow		mWindow;
		World					mWorld;
		Player                  mPlayer;
};

#endif // GAME_H
