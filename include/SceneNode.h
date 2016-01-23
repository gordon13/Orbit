#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/Graphics.hpp>

#include "Category.h"
#include "Command.h"
#include "CommandQueue.h"

#include <algorithm>
#include <memory>
#include <vector>
#include <assert.h>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode>  Ptr;

    public:
                            SceneNode();

        void                attachChild(Ptr child);
        Ptr                 detachChild(const SceneNode& node);

        void                update(sf::Time dt, CommandQueue& commands);

        sf::Vector2f        getWorldPosition() const;
        sf::Transform       getWorldTransform() const;

        void				onCommand(const Command& command, sf::Time dt);
        virtual unsigned int getCategory() const;

    private:
        virtual void        updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void        updateChildren(sf::Time dt, CommandQueue& commands);

        virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void			    drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<Ptr>    mChildren;
        SceneNode*          mParent;
};

#endif // SCENENODE_H
