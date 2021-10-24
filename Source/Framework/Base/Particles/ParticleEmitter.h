#ifndef __PARTICLEEMITTER__H__
#define __PARTICLEEMITTER__H__

#include "Particle.h"

class ParticleSystem;

/*The particel emitter stores the particles, updates them and is in charge of setting them and firing the,*/
class ParticleEmitter
{
public:
    ParticleEmitter(unsigned int maxParticles, ParticleSystem* ownerParticleSystem);
    ~ParticleEmitter();

    void fireParticles(unsigned int amountOfParticles, float firingAngle, float speed);
    
    void update(double delta);
    
    void setEmitterPosition(Vector2 aPosition){ m_Position = aPosition; }
    void setInactiveParticle(unsigned int index, Vector4Int color, Vector2 size, double duration);
    void setAllParticles(Vector4Int color, Vector2 size, double duration);

	unsigned int getMaxNumberParticles() { return m_MaxNumberParticles; }
    
    void setSpeedRange(float aRange){ m_SpeedRange = aRange; }
    void setFiringAngleRange(float aRange){ m_FiringAngleRange = aRange; }
    void setSize(Vector2 aSize){ m_Size = aSize; }

private:

	//Variables used when generating a "random" firing range
    float m_FiringAngleRange;
    float m_SpeedRange;

	unsigned int m_MaxNumberParticles;

    Vector2 m_Position;
    Vector2 m_Size;

    Pool<Particle>m_PoolParticles;
    ParticleSystem* m_OwnerParticleSystem;
};

#endif