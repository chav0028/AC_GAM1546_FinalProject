#pragma once

#include <vector>
#include <string>

class Scene;
class Component;
class TransformComponent;

class Entity
{
public:
	Entity(Vector2 position, Vector2 size,Scene* ownerScene, std::string name);
	~Entity();

    virtual void loadContent();
    virtual void update(double delta);
    virtual void draw();
    virtual void reset();

    Scene* getSceneOwner(){ return m_SceneOwner; }

    void addComponent(Component* component);
    void removeComponent(Component* component);
    Component* getComponent(unsigned int aIndex);

    bool getEnabled(){ return m_Enabled; }
    void setEnabled(bool aEnabledStatus){ m_Enabled = aEnabledStatus; }

    void attachChild(Entity* child);
	Entity*	detachChild(const Entity& child);

	Vector2 getPosition();
	void setPosition(Vector2 position);

	Vector2 getSize();
	void setSize(Vector2 size);

	Vector2 getScale();
	void setScale(Vector2 scale);

private:
    bool m_Enabled;
    TransformComponent* m_TransformComponent;
    
    std::vector<Component*>m_listOfComponents;
    std::string m_entityName;

    Entity* m_parent;
    std::vector<Entity*> m_children;

    virtual void updateCurrent(double delta);
    void updateChildren(double delta);

    virtual void drawCurrent();
    void drawChildren();

    Scene* m_SceneOwner;
};

