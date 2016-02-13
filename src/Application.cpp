#include "Application.h"
#include <Utility.h>
#include <State.h>
#include <StateIdentifiers.h>
#include <TitleState.h>
#include <GameState.h>
#include <MenuState.h>
#include <PauseState.h>
#include <SettingsState.h>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode(1024, 800), "Orbit", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "resources/fonts/GlacialIndifference-Regular.otf");

	mTextures.load(Textures::TitleScreen, "resources/title_screen.png");
	mTextures.load(Textures::ButtonNormal,		"resources/button_normal.png");
	mTextures.load(Textures::ButtonSelected,	"resources/button_selected.png");
	mTextures.load(Textures::ButtonPressed,		"resources/button_pressed.png");

	registerStates();
	mStateStack.pushState(States::Title);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);

            if (mStateStack.isEmpty())
				mWindow.close();

        }
        render();
    }
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		//mPlayer.handleEvent(event);
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingsState>(States::Settings);
}


