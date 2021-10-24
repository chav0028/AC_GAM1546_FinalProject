
#ifndef __Projectile__H__
#define __Projectile__H__


#include "../Source/Framework/Services/Pool.h"

const ShaderProgramIndex PROJECTILE_DEFAULT_SHADER = ShaderProgramIndex_VaryingColor;

/*The class projetiles handles setting and making use of hte correct information when it is fired..*/
class Projectile : public GameObject
{
public:
    Projectile();//Special constructor, because this doesn't content a load content function
    Projectile(Pool<Projectile>* pool);//if the projectile is part of a pool

    ~Projectile();

    virtual void reset();

    virtual void fire(double duration, float direction, Vector2 launchPosition, float speed, int attackDamage);

    virtual void update(double delta);

    int getAttackDamage();

    void deactivateProjectile();

protected:
    int m_AttackDamage;
    double m_Duration;

    Pool<Projectile>* m_PoolOwner;//the pool in which the projectile is
};


#endif
