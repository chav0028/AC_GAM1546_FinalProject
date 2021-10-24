#include "CommonHeader.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent(Vector2 aPosition, Vector2 aSize, Entity* aOwner,Vector2 aScale ) : Component(aOwner, "TransformComponent"),
m_Position(aPosition),
m_Size(aSize),
m_Scale(aScale)
{
}

TransformComponent::~TransformComponent()
{
}
