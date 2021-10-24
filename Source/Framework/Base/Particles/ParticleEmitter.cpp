/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : Emits the particles from a pool

December 14
-Chande emitter to have more random values
*/


#include "CommonHeader.h"

using namespace std;

ParticleEmitter::ParticleEmitter(unsigned int aMaxParticles, ParticleSystem* ownerParticleSystem):
m_PoolParticles(aMaxParticles),
m_MaxNumberParticles(aMaxParticles),
m_OwnerParticleSystem(ownerParticleSystem),
m_FiringAngleRange(0),
m_SpeedRange(0),
m_Size(1,1)
{
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::fireParticles(unsigned int aAmountOfParticles, float aFiringAngle, float aSpeed)
{
        for (unsigned int i = 0; i < aAmountOfParticles; i++)
        {
            Particle* tempParticle = m_PoolParticles.getActivateObject();//Get and activate a particle
            float fireAngle;//The actual angle in which the projectile will be fired
            float fireSpeed; //The actual speed in which the projectile will be fired

            if (tempParticle != nullptr)//Check it is a valid particle
            {
                //Check if the particle will need a random firing angle
                if (m_FiringAngleRange > 0)//If the particle angle is going to be from a random range
                {
                    float minAngle = aFiringAngle - m_FiringAngleRange / 2;//Get the least possible firing angle
                    float maxAngle = aFiringAngle + m_FiringAngleRange / 2;//Get the max possible firing range

                    //min + (std::rand() % (max - min + 1))- Get a random number between a range
                    fireAngle = minAngle + rand() % (unsigned int)(maxAngle - minAngle + 1);//Get a random number between min angle and max angle.Cast to unsigned int for rand to work 
                }
                else//If the particle is going to have an exact angle
                {
                    fireAngle = aFiringAngle;
                }

                //Check if the particle will need a random speed
                if (m_SpeedRange > 0)//If the particle speed is going to be from a random range
                {
                    float minSpeed = aSpeed - m_SpeedRange / 2;//Get the least possible firing angle
                    float maxSpeed = aSpeed + m_SpeedRange / 2;//Get the max possible firing range

                    //min + (std::rand() % (max - min + 1))- Get a random number between a range
                    fireSpeed = minSpeed + std::rand() % (unsigned int)(maxSpeed - minSpeed + 1);//Get a random number between min speed and max speed.Cast to unsigned int for rand to work with % 
                }
                else//If the particle is going to have an exact angle
                {
                    fireSpeed = aSpeed;
                }

                //Calculate a random position inside the size of the emitter
                Vector2 positionInEmitter = m_Position;

                float halfWidth = m_Size.x / 2;
                float halfHeight = m_Size.y / 2;
                float minX = m_Position.x - halfWidth;
                float maxX = m_Position.x + halfWidth;
                float minY = m_Position.y - halfHeight;
                float maxY = m_Position.y+ halfHeight;

                //Get a random x and y value
                float randomX = minX + rand() % (unsigned int)(maxX - minX + 1);
                float randomY = minY + rand() % (unsigned int)(maxY - minY + 1);

                tempParticle->fireParticle(Vector2(randomX,randomY), fireAngle, fireSpeed);//Fire the particle
            }
        }
}


void ParticleEmitter::update(double aDelta)
{
    std::vector<Particle*> currrentlyActiveParticles = m_PoolParticles.getCurrentlyActiveObjects();//Get the particles that are active

	for (unsigned int i = 0; i < currrentlyActiveParticles.size(); i++)//Go through all the active particles
	{
		if (currrentlyActiveParticles.at(i) != nullptr)
		{
			currrentlyActiveParticles.at(i)->update(aDelta);//Update each particle

			//Add all the active particles to the renderer so that they are drawn
            ParticleRenderer* renderer = m_OwnerParticleSystem->getParticleRenderer();
            if (renderer != nullptr)
            {   
                renderer->addParticle(*currrentlyActiveParticles.at(i));
            }
		}
	}
}

void ParticleEmitter::setInactiveParticle(unsigned int aIndex, Vector4Int aColor, Vector2 aSize, double aDuration)
{
    if (aIndex < m_MaxNumberParticles)//If it is a valid index
    {
        Particle* inactiveParticle = m_PoolParticles.getInactiveObject(aIndex);//Get an inactive particle DOESN'T acitvate it

        if (inactiveParticle!=nullptr)
        {
            inactiveParticle->setParticle(aColor, aSize, aDuration);//Set the particle
        }
    }
}

void ParticleEmitter::setAllParticles(Vector4Int aColor, Vector2 aSize, double aDuration)
{
    //Set the active particles
    std::vector<Particle*> currrentlyActiveParticles = m_PoolParticles.getCurrentlyActiveObjects();//Get the particles that are active

    for (unsigned int i = 0; i < currrentlyActiveParticles.size(); i++)//Go through all the active particles
    {
        currrentlyActiveParticles.at(i)->setParticle(aColor, aSize, aDuration);//set each particle
    }

    //Set the inactive particles
    std::vector<Particle*> currrentlyInactiveParticles = m_PoolParticles.getCurrentlyInactiveObjects();//Get the particles that are inactive

    for (unsigned int i = 0; i < currrentlyInactiveParticles.size(); i++)//Go through all the inactive particles
    {
        currrentlyInactiveParticles.at(i)->setParticle(aColor, aSize, aDuration);//set each particle
    }

}