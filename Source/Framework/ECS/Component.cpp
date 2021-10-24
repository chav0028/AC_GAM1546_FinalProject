#include "CommonHeader.h"

Component::Component(Entity* aOwner, std::string aName):
	m_OwnerEntity(aOwner),
	m_Name(aName),
	m_Enabled(true)
{

}

Component::~Component()
{
}

//Empty so that they can be overwritten
void Component::update(double delta)
{
}

void Component::draw()
{
}