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
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);

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

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt, mCommandQueue);
	adaptPlayerPosition();
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
	//mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Space, "resources/space1.bmp");
	mTextures.load(Textures::Earth, "resources/earth.png");
	mTextures.load(Textures::Moon, "resources/moon.png");
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

