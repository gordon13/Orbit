#include "SceneNode.h"
#include "Command.h"

SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
    [&] (Ptr& p) -> bool { return p.get() == &node; });

    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time, CommandQueue&)
{
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
    {
        (*itr)->update(dt, commands);
    }
}

void SceneNode::draw(   sf::RenderTarget& target,
                        sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);


    // debug purposes
    drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&,
                            sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
    {
        (*itr)->draw(target, states);
    }
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this;
        node != nullptr; node = node->mParent)
    transform = node->getTransform() * transform;
    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    if (command.category & getCategory())
        command.action(*this, dt);
    //FOREACH(Ptr& child, mChildren)
    //    child->onCommand(command, dt);
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
    {
        (*itr)->onCommand(command, dt);
    }
}

bool SceneNode::isDestroyed() const
{
	// By default, scene node needn't be removed
	return false;
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(5.f);

	target.draw(shape);
}
sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

	FOREACH(Ptr& child, sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
    if (this != &node && collision(*this, node))
        collisionPairs.insert(std::minmax(this, &node));

    FOREACH(Ptr& child, mChildren)
        child->checkNodeCollision(node, collisionPairs);
}

void SceneNode::compareSceneNodes(SceneNode& sceneGraph, std::set<Pair>& objPairs)
{
    compareNodes(sceneGraph, objPairs);

	FOREACH(Ptr& child, sceneGraph.mChildren)
		compareSceneNodes(*child, objPairs);
}

void SceneNode::compareNodes(SceneNode& node, std::set<Pair>& objPairs)
{
    if (this != &node /*&& collision(*this, node)*/)
        objPairs.insert(std::minmax(this, &node));

    FOREACH(Ptr& child, mChildren)
        child->compareNodes(node, objPairs);
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}
