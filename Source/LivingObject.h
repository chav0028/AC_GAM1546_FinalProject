#ifndef __LIVINGOBJECT__H__
#define __LIVINGOBJECT__H__

#include "Framework/Base/GameObject.h"
#include <string>

/*Child class of gameobject used to handle the concept of hitpoints easily*/
class LivingObject : public GameObject
{
public:
    LivingObject(int maxHealth, ShaderProgramIndex indexShaderProgram, std::string name);
    ~LivingObject();

    virtual void update(double delta);
    virtual void applyDamage(int damage);
    virtual void onDeath();

    unsigned int getMaxHealth(){ return m_MaxHealth; }
    
    unsigned int getHealth(){ return m_Health; }
    void replenishFullHealth();
    void setHealth(int health);

    int getCollisionDamage(){ return m_CollisionDamage; }
    void setCollisionDamage(int aDamage){ m_CollisionDamage = aDamage; }

    virtual void reset();

    bool getAlive(){ return m_Alive; }

    void useDeathAnimationShader(){ m_IndexShaderProgramToUse = m_DeathAnimationShader; }
    void useRegularShader(){ m_IndexShaderProgramToUse = m_RegularShader; }

protected:
    ShaderProgramIndex m_RegularShader;
    ShaderProgramIndex m_DeathAnimationShader;

    bool m_Alive;
    int m_CollisionDamage;
    int m_Health;//Int instead of unsigned int, since when substracting damage the health may become negative
    int m_MaxHealth;
};

#endif