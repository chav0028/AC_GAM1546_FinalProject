/*
Student:    Alvaro Chavez Mixco
Date:       Tuesday, December 14 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Link togetheer the particle emitters with the renderer

December 6
--Modified ParticleSystem.cpp so that it has function updateMaxParticlesCount so that it can keep track of the total max number of particles according to all the emitters.
-In ParticleEmitter.cpp, modified the update method so that all the active particles are added to the renderer;
*/


#include "CommonHeader.h"

///Creates the renderer
ParticleSystem::ParticleSystem(ShaderProgramIndex aIndexShaderProgram, GLuint aTexture):
	m_IndexShaderProgramToUse(aIndexShaderProgram),
	m_MaxParticles(0),
	m_ParticleRenderer(nullptr)
{
	m_ParticleRenderer = new ParticleRenderer(this,aTexture);
}

//Creates the render and a emitter
ParticleSystem::ParticleSystem(unsigned int aMaxParticles, ShaderProgramIndex aIndexShaderProgram, GLuint aTexture):
	m_IndexShaderProgramToUse(aIndexShaderProgram),
	m_ParticleRenderer(nullptr)
{
	createAddParticleEmitter(aMaxParticles);//Create the particle emitter, this is done first. So that ther renderer
	//can create a block of memory of the right size.
	m_ParticleRenderer = new ParticleRenderer(this, aTexture);
}


ParticleSystem::~ParticleSystem()
{
	//Delete all the emitters
	while (m_ParticleEmitters.empty() == false)
	{
		//Delete the emitter
		if (m_ParticleEmitters.back() != nullptr)
		{
			delete m_ParticleEmitters.back();
			m_ParticleEmitters.back() = nullptr;
		}

		//Remove from vector
		m_ParticleEmitters.pop_back();
	}

	//Delete the renderer
	if (m_ParticleRenderer != nullptr)
	{
		delete m_ParticleRenderer;
		m_ParticleRenderer = nullptr;
	}

}

ShaderProgram * ParticleSystem::getShaderProgramFromIndex()
{
	return GameFramework::getInstance()->getResourcesManager()->getShaderProgram(m_IndexShaderProgramToUse);//Return the shader program according to the index stored in the particle system
}

void ParticleSystem::createAddParticleEmitter(unsigned int aMaxNumberParticles)
{
	m_ParticleEmitters.push_back(new ParticleEmitter(aMaxNumberParticles,this));//Create and add a new emiiter
}

void ParticleSystem::addParticleEmitter(ParticleEmitter * aEmitter)
{
	if (aEmitter != nullptr)
	{
		m_ParticleEmitters.push_back(aEmitter);//Add the emiter to vector
	}
}

ParticleEmitter * ParticleSystem::getParticleEmitter(unsigned int aIndex)
{
	if (aIndex < m_ParticleEmitters.size())
	{
		return m_ParticleEmitters.at(aIndex);//Return the emitter at the index
	}

	return nullptr;//If the index is out of range return null
}

void ParticleSystem::update(double aDelta)
{
	//Reset the renderer
	if (m_ParticleRenderer != nullptr)
	{
		//Reset the particle render
		m_ParticleRenderer->setNumberOfParticles(0);
	}

	//Update all the emitters
	for (unsigned int i = 0; i < m_ParticleEmitters.size(); i++)
	{
		if (m_ParticleEmitters.at(i) != nullptr)
		{
			m_ParticleEmitters.at(i)->update(aDelta);
		}
	}

}

void ParticleSystem::draw(Vector2 aCameraPosition, Vector2 aProjectionScale)
{
	if (m_ParticleRenderer != nullptr)
	{
        m_ParticleRenderer->draw(aCameraPosition, aProjectionScale);//Draw the particle renderer
	}
}