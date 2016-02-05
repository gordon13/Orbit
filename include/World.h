#ifndef WORLD_H
#define WORLD_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Ship.h"
#include "Planet.h"
#include <CommandQueue.h>
#include <Command.h>
#include "PhysicsManager.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

namespace sf
{
    class RenderWindow;
}

class World : private sf::NonCopyable
{
    public:
        explicit                World(sf::RenderWindow& window, FontHolder& fonts);
        void                    update(sf::Time dt);
        void                    draw();
        CommandQueue&			getCommandQueue();

    private:
        void                    loadTextures();
        void                    buildScene();
        void                    addPlanets();
        void					addPlanet(Planet::Type type, float relX, float relY);
        void					spawnPlanets();

        void                    adaptPlayerVelocity();
        void					adaptPlayerPosition();
        void					handleCollisions();
        sf::FloatRect			getViewBounds() const;




    private:
        enum Layer
        {
            Background,
            Main,
            LayerCount
        };

        struct SpawnPoint
		{
			SpawnPoint(Planet::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
			{
			}

			Planet::Type type;
			float x;
			float y;
		};

    private:
        sf::RenderWindow&       mWindow;
        sf::View                mWorldView;
        TextureHolder           mTextures;
        FontHolder&				mFonts;
        SceneNode               mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;
        CommandQueue            mCommandQueue;

        sf::FloatRect           mWorldBounds;
        sf::Vector2f			mSpawnPosition;
        float                   mScrollSpeed;
        Ship*                   mPlayerShip;

        std::vector<SpawnPoint>		mPlanetSpawnPoints;


        // physics
        PhysicsManager          mPhysicsManager;
};

#endif // WORLD_H
