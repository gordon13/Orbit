#ifndef APPLICATION_H
#define APPLICATION_H

#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include <World.h>
#include <Player.h>
#include <StateStack.h>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

class Application
{
    public:
								Application();
		void					run();


	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					updateStatistics(sf::Time dt);
		void					registerStates();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		TextureHolder			mTextures;
	  	FontHolder				mFonts;
		Player					mPlayer;

		StateStack				mStateStack;

};

#endif
