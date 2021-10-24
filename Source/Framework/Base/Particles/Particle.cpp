/*
Student:    Alvaro Chavez Mixco
Date:       Tuesday, December 14 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Apply the properties for which the projectile was fired

December 6
-In Particles.cpp, modified the fireParticle function so that it can fire a particle between a
//range of angles and a range of speed.
*/

#include "CommonHeader.h"

Particle::Particle(Pool<Particle>* aPool):
	m_Position(Vector2(0.0f,0.0f)),
	m_Speed(0.0f),
    m_Angle(0.0f),
    m_Color(Vector4Int(0, 0, 0, 0)),
	m_Size(Vector2(0.0f,0.0f)),
	m_Duration(100),
    m_PoolOwner(aPool),
    m_Enabled(false)
{
    m_RemainingTime = m_Duration;//Reset timer
}

void Particle::setParticle(Vector4Int aColor, Vector2 aSize, double aDuration)
{
    m_Color = aColor;
    m_Size = aSize;
    m_Duration = aDuration;
    m_RemainingTime = m_Duration;//Reset timer
}

void Particle::fireParticle(Vector2 aStartingPosition, float aAngle,float aSpeed)
{
    m_Enabled = true;
    m_Position = aStartingPosition;
    m_Angle = aAngle;
    m_Speed = aSpeed;
}

Particle::~Particle()
{
}

void Particle::update(double aDelta)
{
    //If the particle is enabled
    if (m_Enabled == true)
    {
        //Move the particle
        //Convert angle to radians
        float angleRad = m_Angle*PI / 180.0f;//Multiply angle in degrees by PI, and divide by 180

        float stepX = cosf(angleRad)*(m_Speed*(float)aDelta);//Calculate the movement on X axis
        float stepY = sinf(angleRad)*(m_Speed*(float)aDelta);//Calculate movement on Y axis

        m_Position = m_Position + Vector2(stepX, stepY);//Add the amount we moved to the current position

        //Reduce the life of the parameter
        m_RemainingTime -= aDelta;
        m_Color.w -= (int)aDelta;//Reduce alpha (may not be even be used by shader)

        //If the time of the particle is over
        if (m_RemainingTime <= 0)
        {
            m_Enabled = false;//Disable the particle
            m_RemainingTime = m_Duration;//Restart the duration timer

            //If the particle belongs to a pool
            if (m_PoolOwner != nullptr)
            {
               m_PoolOwner->deactivateObject(this);//Tell the pool to deactivate this particle
                m_RemainingTime = m_Duration;//Reset timer
            }
        }      
    }
}
