/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose :Contains a projectile hat simply goes where it is aimed
*/
#include "CommonHeader.h"

Projectile::Projectile()
    : GameObject(PROJECTILE_DEFAULT_SHADER,"Projectile"),
    m_PoolOwner(nullptr),
    m_Duration(0),
    m_AttackDamage(0)
{
    setMesh(GameFramework::getInstance()->getResourcesManager()->getMesh(MESH_PROJECTILE_INDEX));
}

Projectile::Projectile(Pool<Projectile>* aPool)
    : GameObject(PROJECTILE_DEFAULT_SHADER, "PoolProjectile"),
    m_PoolOwner(aPool),
    m_Duration(0),
    m_AttackDamage(0)
{
    setMesh(GameFramework::getInstance()->getResourcesManager()->getMesh(MESH_PROJECTILE_INDEX));
}

Projectile::~Projectile()
{
}

void Projectile::reset()
{
    deactivateProjectile();
}

void Projectile::update(double aDelta)
{
    if (m_Enabled == true)//If the object is enabled
    {
        MoveGameObjectAngleSpeed(aDelta);//Move the projectile

        m_Duration -= aDelta;

        //iF its duration runs out
        if (m_Duration <= 0)
        {
            deactivateProjectile();//Deactivate it.
        }

        //if the projectile goes out of bounds deactivate it
        if (boundsCollisionActiveScene() == true)
        {
            deactivateProjectile();
        }

    }
}

void Projectile::fire(double aDuration, float aDirection, Vector2 aLaunchPosition, float aSpeed, int aAttackDamage)
{
    //set stats
    m_Position = aLaunchPosition;
    setAngle(aDirection);
    m_Speed = aSpeed;
    m_AttackDamage = aAttackDamage;
    m_Duration = aDuration;

    //Enable projectile
    m_Enabled=true;
}

//Disables the projectile, and if it belongs to a pool, it tells the pool to remove it
void Projectile::deactivateProjectile()
{
    //Disable the projectile
    m_Enabled=false;

    if (m_PoolOwner != nullptr)//If the object is in a pool
    {
        //Tell the pool to move the projectile to the inactive list
        m_PoolOwner->deactivateObject(this);
    }
}

int Projectile::getAttackDamage()
{
    return m_AttackDamage;
}