#pragma once
#include "Component.h"

class TransformComponent :
    public Component
{
public:
	TransformComponent(Vector2 position, Vector2 size, Entity* owner, Vector2 scale = Vector2(1.0f, 1.0f));
	~TransformComponent();
	
	Vector2 getPosition(){ return m_Position; }
    void setPosition(Vector2 position){ m_Position = position; }
    
	Vector2 getSize() { return m_Size; }
	void setSize(Vector2 size){ m_Size = size; }

	Vector2 getScale() { return m_Scale; }
	void setScale(Vector2 scale) { m_Scale = scale; }

private:
    Vector2 m_Position;
    Vector2 m_Size;
	Vector2 m_Scale;
};