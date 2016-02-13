#include "Ship.h"
#include "DataTables.h"
#include "ResourceHolder.h"
#include "DataTables.h"
#include "Utility.h"
#include "CommandQueue.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
    const std::vector<ShipData> Table = initializeShipData();
}

Ship::Ship(Type type, const TextureHolder& textures, const FontHolder& fonts)
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

void Ship::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Ship::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    const float* matrix = this->getWorldTransform().getMatrix();
	// Update enemy movement pattern; apply velocity
	//updateMovementPattern(dt);

	Entity::updateCurrent(dt, commands);

	// Update texts
	updateTexts();
}

float Ship::getMaxThrust() const
{
	return Table[mType].speed;
}

float Ship::getMaxRotateVelocity() const
{
	return Table[mType].rotateVelocity;
}

unsigned int Ship::getCategory() const
{
    switch (mType)
    {
        case Basic:
            return Category::PlayerShip;
        case Super:
            return Category::PlayerShip;
        default:
            return Category::PlayerShip;
    }
}




void Ship::updateTexts()
{
	mHealthDisplay->setString(toString(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	//mHealthDisplay->setRotation(-getRotation());
}

sf::FloatRect Ship::getBoundingRect() const
{
    return getWorldTransform()
        .transformRect(mSprite.getGlobalBounds());

}

