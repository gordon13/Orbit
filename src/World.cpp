#include "World.h"

#include "TextNode.h"

#include <SFML/Graphics/RenderWindow.hpp>


World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mFonts(fonts)
, mTextures()
, mSceneGraph()
, mSceneLayers()
//, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mWorldBounds(0.f, 0.f, 3000, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerShip(nullptr)
, mPhysicsManager()
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
    mWorldView.zoom(3);
	spawnPlanets();
}

void World::update(sf::Time dt)
{
	// Scroll the world, reset player velocity
	//mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	//mWorldView.setPosition(0.f, 500.f);
	mWorldView.move(mPlayerShip->getVelocity().x * dt.asSeconds(), mPlayerShip->getVelocity().y * dt.asSeconds());

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

    // apply physics to world
    handlePhysics();

    // Collision detection and response (may destroy entities)
	handleCollisions();

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt, mCommandQueue);
	adaptPlayerPosition();

	//apply physics
	mPhysicsManager.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::Basic, "resources/doge.bmp");
	mTextures.load(Textures::Space, "resources/space1.bmp");
	mTextures.load(Textures::Earth, "resources/earth.png");
	mTextures.load(Textures::Moon, "resources/moon.png");
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	FOREACH(SceneNode::Pair pair, collisionPairs)
	{
		if (matchesCategories(pair, Category::PlayerShip, Category::Planet))
		{
			auto& player = static_cast<Ship&>(*pair.first);
			sf::Vector2f playerPos= player.getPosition();
			sf::Vector2f playerVel = player.getVelocity();
			auto& planet = static_cast<Planet&>(*pair.second);
			sf::Vector2f planetPos= planet.getPosition();
			sf::Vector2f planetVel = planet.getVelocity();

            sf::Vector2f diff = playerPos - planetPos;
			// Collision: Player damage = enemy's remaining HP
			//player.damage(enemy.getHitpoints());
			//enemy.destroy();
			printf("Hit!");
            /*if  ( diff.x > 0) {
                player.setVelocity(playerVel.x * -1, playerVel.y * -1);
            } else {
                //player.setVelocity(playerVel.x * -1, playerVel.y * -1);
            }*/

            // do per pixel collision here


		}

		/*else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			// Apply pickup effect to player, destroy projectile
			pickup.apply(player);
			pickup.destroy();
		}

		else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
			  || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		{
			auto& aircraft = static_cast<Aircraft&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			// Apply projectile damage to aircraft, destroy projectile
			aircraft.damage(projectile.getDamage());
			projectile.destroy();
		}*/
	}
}

void World::handlePhysics()
{
    std::set<SceneNode::Pair> physicsPairs;
	mSceneGraph.compareSceneNodes(mSceneGraph, physicsPairs);

	FOREACH(SceneNode::Pair pair, physicsPairs)
	{
	    //cout << matchesCategories(pair, Category::PlayerShip, Category::Planet) << endl;
		if (matchesCategories(pair, Category::PlayerShip, Category::Planet) /*|| matchesCategories(pair, Category::Planet, Category::Planet)*/)
		{
            auto& obj1 = static_cast<Ship&>(*pair.first);
            float obj1Mass= obj1.getMass();
			sf::Vector2f obj1Pos= obj1.getPosition();
			sf::Vector2f obj1Vel = obj1.getVelocity();

			auto& obj2 = static_cast<Planet&>(*pair.second);
			float obj2Mass= obj2.getMass();
			sf::Vector2f obj2Pos= obj2.getPosition();
			sf::Vector2f obj2Vel = obj2.getVelocity();

            sf::Vector2f distanceVector = obj1Pos - obj2Pos;

            //float distance = sqrt((obj1Pos.x - obj2Pos.x)*(obj1Pos.x - obj2Pos.x) + (obj1Pos.y - obj2Pos.y)*(obj1Pos.y - obj2Pos.y);
            float distance = sqrt((distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y));


			float gravity = (obj1Mass * obj2Mass) / (distance); // f= ma

			sf::Vector2f obj1ToObj2Norm = obj2Pos - obj1Pos;
			float length1 = sqrt((obj1ToObj2Norm.x * obj1ToObj2Norm.x) + (obj1ToObj2Norm.y * obj1ToObj2Norm.y));
            if (length1 != 0)
                obj1ToObj2Norm = sf::Vector2f(obj1ToObj2Norm.x / length1, obj1ToObj2Norm.y / length1);

            // disabled gravity between planets because it makes things crazy!
            //sf::Vector2f obj2ToObj1Norm = obj2Pos - obj1Pos;
            //float length2 = sqrt((obj2ToObj1Norm.x * obj2ToObj1Norm.x) + (obj2ToObj1Norm.y * obj2ToObj1Norm.y));
            //if (length2 != 0)
            //    obj2ToObj1Norm = sf::Vector2f(obj2ToObj1Norm.x / length2, obj2ToObj1Norm.y / length2);

            sf::Vector2f obj1ToObj2 = obj1ToObj2Norm; //normalise direction vector
            //sf::Vector2f obj2ToObj1 = obj2ToObj1Norm; //normalise direction vector

            obj1.accelerate( (obj1ToObj2 * gravity) / obj1Mass);
            //obj2.accelerate( (obj2ToObj1 * gravity) / obj2Mass);
		}
	}
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Space);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's ship
	std::unique_ptr<Ship> player(new Ship(Ship::Basic, mTextures, mFonts));
	mPlayerShip = player.get();
	mPlayerShip->setPosition(mSpawnPosition);
	mSceneLayers[Main]->attachChild(std::move(player));

    // Populate world with planets
    addPlanets();
    spawnPlanets();
}

void World::addPlanets()
{
	// Add enemies to the spawn point container
	addPlanet(Planet::Earth,    0.f,  20.f);
	addPlanet(Planet::Moon,    200.f,  1000.f);

	// Sort all enemies according to their y value, such that lower enemies are checked first for spawning
	std::sort(mPlanetSpawnPoints.begin(), mPlanetSpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.y < rhs.y;
	});
}

void World::addPlanet(Planet::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, relX, relY);
	mPlanetSpawnPoints.push_back(spawn);
}

void World::spawnPlanets()
{
	// Spawn all enemies entering the view area (including distance) this frame
	while (!mPlanetSpawnPoints.empty())
	{
		SpawnPoint spawn = mPlanetSpawnPoints.back();

		std::unique_ptr<Planet> planet(new Planet(spawn.type, mTextures, mFonts));
		planet->setPosition(spawn.x, spawn.y);
		//mPhysicsManager.registerEntity(planet);
		//planet->setRotation(180.f);

		mSceneLayers[Main]->attachChild(std::move(planet));

		// Enemy is spawned, remove from the list to spawn
		mPlanetSpawnPoints.pop_back();
	}
}
void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	/*sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerShip->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerShip->setPosition(position);*/
}

void World::adaptPlayerVelocity()
{
	/*sf::Vector2f velocity = mPlayerShip->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerShip->setVelocity(velocity / std::sqrt(2.f));*/
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}


