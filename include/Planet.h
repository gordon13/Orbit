#ifndef PLANET_H
#define PLANET_H


#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "ResourceIdentifiers.h"
#include "TextNode.h"

#include <SFML/Graphics/Sprite.hpp>

class Planet : public Entity
{
    public:
        enum Type
        {
            Earth,
            Moon,
            TypeCount
        };

    public:
                        Planet(   Type type,
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

#endif // PLANET_H
