#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"

#include <SFML/Graphics/Sprite.hpp>

class Ship : public Entity
{
    public:
        enum Type
        {
            Basic,
            Super,
            TypeCount
        };

    public:
                        Ship(   Type type,
                                const TextureHolder& textures,
                                const FontHolder&);

        virtual unsigned int getCategory() const;

    private:
        virtual void    drawCurrent(sf::RenderTarget& target,
                                    sf::RenderStates states) const;
        virtual void 	updateCurrent(  sf::Time dt,
                                        CommandQueue& commands);
        void			updateTexts();


    private:
        Type            mType;
        TextNode*       mHealthDisplay;
        sf::Sprite      mSprite;
};

#endif // SHIP_H
