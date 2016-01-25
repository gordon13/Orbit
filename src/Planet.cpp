#include "Planet.h"
#include "DataTables.h"
#include "ResourceHolder.h"
#include "DataTables.h"
#include "Utility.h"
#include "CommandQueue.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
    const std::vector<PlanetData> Table = initializePlanetData();
}

Planet::Planet(Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].hitpoints, Table[type].mass)
, mType(type)
, mSprite(textures.get(Table[type].texture))
, mHealthDisplay(nullptr)
{
    centerOrigin(mSprite);

    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
    mHealthDisplay = healthDisplay.get();
    attachChild(std::move(healthDisplay));

}

void Planet::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Planet::updateCurrent(sf::Time dt, CommandQueue& commands)
{

	// Update enemy movement pattern; apply velocity
	//updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	// Update texts
	updateTexts();
}

unsigned int Planet::getCategory() const
{
    switch (mType)
    {
        case Earth:
            return Category::Planet;
        case Moon:
            return Category::Planet;
        default:
            return Category::Planet;
    }
}

void Planet::updateTexts()
{
	mHealthDisplay->setString(toString(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());
}

