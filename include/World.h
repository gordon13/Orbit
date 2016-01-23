#ifndef WORLD_H
#define WORLD_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Ship.h"
#include <CommandQueue.h>
#include <Command.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>

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
        void                    adaptPlayerVelocity();
        void					adaptPlayerPosition();
        sf::FloatRect			getViewBounds() const;


    private:
        enum Layer
        {
            Background,
            Main,
            LayerCount
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
        sf::Vector2f            mSpawnPosition;
        float                   mScrollSpeed;
        Ship*                   mPlayerShip;
};

#endif // WORLD_H
