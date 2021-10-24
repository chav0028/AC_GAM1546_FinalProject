#pragma once

class Entity;

#include <string>

class Component
{
public:
	Component(Entity* owner, std::string name);
	~Component();
	void update(double delta);
	void draw();

protected:
	Entity* m_OwnerEntity;
	std::string m_Name;
	bool m_Enabled;
};

