#ifndef __PARTICLE__H__
#define __PARTICLE__H__

#include "Framework/Services/Pool.h"

const Vector2 PARTICLE_DEFAULT_SIZE = Vector2(2.0f, 2.0f);
const Vector4Int PARTICLE_DEFAULT_COLOR = Vector4Int(255, 255, 0, 255);
const double PARTICLE_DEFAULT_DURATION = 1;
const Vector2 PARTICLES_DEFAULT_SCALE = Vector2(1, 1);
const Vector2 PARTICLES_DEFAULT_UV_SCALE = Vector2(1, 1);
const unsigned int PARTICLES_RENDERER_MAX_NUMBER_OF_PARTICLES = 100000;//The max number of particles that can be displayed


/*The particel handles moving and reducing its timer according to the position it has been given.*/
class Particle//Not inherited from gameobject, since because of the amount we will have on screen,being inherited from it may affect performance
{
public:
    Particle();
    Particle(Pool<Particle>* pool);
    ~Particle();

    void setParticle(Vector4Int color, Vector2 size, double duration);

    void update(double delta);

    void fireParticle(Vector2 startingPosition, float angle,float speed);

    Vector2 getPosition() { return m_Position; }
    void setPosition(Vector2 aPosition) { m_Position = aPosition; }

    Vector2 getSize() { return m_Size; }
    void setSize(Vector2 aSize) { m_Size = aSize; }

    float getSpeed() { return m_Speed; }
    void setVelocity(float aSpeed) { m_Speed = aSpeed; }

    float getAngle(){ return m_Angle; }
    void setAngle(float aAngle){ m_Angle = aAngle; }

    void setDuration(double aDuration) { m_Duration = aDuration; }
    double getDuration() { return m_Duration; }

    void setColor(Vector4Int aColor) { m_Color = aColor; }
    Vector4Int getColor() { return m_Color; }

private:
    Vector2 m_Position;
    float m_Speed;
    float m_Angle;
    Vector4Int m_Color;
    Vector2 m_Size;
    double m_Duration;
    double m_RemainingTime;//Counter of the time the projectile still has left
    bool m_Enabled;

    Pool<Particle>* m_PoolOwner;//the pool in which the projectile is
};

#endif