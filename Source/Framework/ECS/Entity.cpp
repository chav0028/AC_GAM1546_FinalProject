#include "CommonHeader.h"
#include <algorithm>


Entity::Entity(Vector2 aPosition, Vector2 aSize, Scene* aOwnerScene, std::string aName) :
m_parent(nullptr),
m_entityName(aName)
{
    m_TransformComponent = new TransformComponent(aPosition, aSize, this);
    addComponent(m_TransformComponent);
}


Entity::~Entity()
{
    //Delete all the components
    for (unsigned int i = 0; i < m_listOfComponents.size(); i++)
    {
        if (m_listOfComponents.at(i) != nullptr)
        {
            delete m_listOfComponents.at(i);
            m_listOfComponents.at(i) = nullptr;
        }
    }

    //Delete all the children
    for (unsigned int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i) != nullptr)
        {
            delete m_children.at(i);
            m_children.at(i) = nullptr;
        }
    }

}

void Entity::update(double aDelta)
{
    updateCurrent(aDelta);//Update this object,in a entity component system it would update all children
    updateChildren(aDelta);
}

void Entity::reset()
{
    //Reset all the children
    for (unsigned int i = 0; i < m_children.size(); i++)
    {
        if (m_children.at(i) != nullptr)
        {
            m_children.at(i)->reset();
        }
    }
}

void Entity::draw()
{
    drawCurrent();
    drawChildren();
}

void Entity::loadContent()
{
    //Load all the children
    for (unsigned int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->loadContent();
    }
}

void Entity::addComponent(Component* aComponent)
{
    if (aComponent != nullptr)
    {
        m_listOfComponents.push_back(aComponent);
    }

}

void Entity::removeComponent(Component* aComponent)
{
    std::vector<Component*>::iterator it;
    int i = 0;//I is the current value in the for loop, since .at doesn't take an iterator as a value

    for (it = m_listOfComponents.begin(); it < m_listOfComponents.end(); it++)//Go through vector
    {
        if (m_listOfComponents.at(i) == aComponent)//If element is found
        {
            m_listOfComponents.erase(it);//erase it
        }
        i++;
    }
}

Component* Entity::getComponent(unsigned int aIndex)
{

    if (aIndex >= 0 && aIndex<m_listOfComponents.size())//Check that the index is in a valid range
    {
        return m_listOfComponents.at(aIndex);
    }

    return nullptr;
}

void Entity::attachChild(Entity* child)
{
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

Entity* Entity::detachChild(const Entity& node)
{
    auto found = std::find_if(m_children.begin(), //Go through all the children 
        m_children.end(),
        [&](Entity* p) //It assigns the value to temporary variable P
    { return p == &node; });//If p is equal to the one we are looking
    //If we find the value, assign it to found.

    Entity* result = std::move(*found);//Move the content in found
    result->m_parent = nullptr;//Set that the parent is null, so we can later attach it to other object.
    m_children.erase(found);//Delete the found pointer
    return result;//Return the result, in case we want to later attach it to something else
}

Vector2 Entity::getPosition()
{
	//Check if the transform component is valid
	if (m_TransformComponent != nullptr)
	{
		return m_TransformComponent->getPosition();//Return the position from transform component
	}

	//If there is no transform component
	return Vector2(0, 0);
}

void Entity::setPosition(Vector2 aPosition)
{
	//If it is a valid transform component 
	if (m_TransformComponent != nullptr)
	{
		m_TransformComponent->setPosition(aPosition);//Set its position
	}
}

Vector2 Entity::getSize()
{
	//Check if the transform component is valid
	if (m_TransformComponent != nullptr)
	{
		return m_TransformComponent->getSize();//Return the size from transform component
	}

	//If there is no transform component
	return Vector2(0, 0);
}

void Entity::setSize(Vector2 aSize)
{
	//If it is a valid transform component 
	if (m_TransformComponent != nullptr)
	{
		m_TransformComponent->setSize(aSize);//Set its size
	}
}

Vector2 Entity::getScale()
{
	//Check if the transform component is valid
	if (m_TransformComponent != nullptr)
	{
		return m_TransformComponent->getScale();//Return the scale from transform component
	}

	//If there is no transform component
	return Vector2(0, 0);
}

void Entity::setScale(Vector2 aScale)
{
	//If it is a valid transform component 
	if (m_TransformComponent != nullptr)
	{
		m_TransformComponent->setScale(aScale);//Set its scale
	}
}

void Entity::updateCurrent(double aDelta)
{
    // Update componnents
    for (unsigned int i = 0; i < m_listOfComponents.size(); i++)
    {
        m_listOfComponents.at(i)->update(aDelta);
    }
}

void Entity::updateChildren(double aDelta)
{
    for (unsigned int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->update(aDelta);
    }

}

void Entity::drawCurrent()
{
    for (unsigned int i = 0; i < m_listOfComponents.size(); i++)
    {
        m_listOfComponents.at(i)->draw();
    }
}

void Entity::drawChildren()
{
    for (unsigned int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->draw();
    }
}