#include "CommonHeader.h"

using namespace std;

LivingObject::LivingObject(int aMaxHealth, ShaderProgramIndex aIndexShaderProgram, std::string aName) :GameObject(aIndexShaderProgram, aName),
m_MaxHealth(aMaxHealth),
m_Health(aMaxHealth),
m_Alive(true),
m_CollisionDamage(0),
m_DeathAnimationShader(ShaderProgramIndex_VertexEffect),
m_RegularShader(aIndexShaderProgram)
{
    m_AnimationTime = 0;
}

LivingObject::~LivingObject()
{
}

void LivingObject::update(double aDelta)
{
    if (m_Alive == false)
    {
        m_AnimationTimer -= aDelta;

        if (m_AnimationTimer <= 0)
        {
            m_Enabled = false;
        }
    }
}


void LivingObject::applyDamage(int aDamage)
{
    m_Health -= aDamage;
    
    if (m_Health <= 0)//If the health is 0 or less
    {
        onDeath();//Set that the user died
    }
}

void LivingObject::onDeath()
{
    m_Alive = false;//Set that the state is dead
    m_IndexShaderProgramToUse = m_DeathAnimationShader;//Set death shader
}

void LivingObject::setHealth(int aHealth)
{
    //Check that the health being set is less than the maximum health possible
    if (aHealth <= m_MaxHealth)
    {
        m_Health = aHealth;//Set health normally

    }
    else if (aHealth > m_MaxHealth)//If the health is bigger than the maximum, set the health to be the maximum
    {
        m_Health = m_MaxHealth;
    }
    else if (aHealth <= 0)//if the health is 0  or less
    {
        m_Health = 0;//Set the health to 0
        onDeath();//Call the onDeath function
    }
    
    //If the health is bigger than 0, ensure the player is alive
    if (m_Health > 0)
    {
        m_Alive = true;
    }

}

void LivingObject::replenishFullHealth()
{
    { m_Health = m_MaxHealth; }//Set health back to maximum health

    //Set player as alive
    m_Alive = true;
}

void LivingObject::reset()
{
    replenishFullHealth();//Replenish the object health completely
    m_AnimationTimer = m_AnimationTime;
    m_IndexShaderProgramToUse = m_RegularShader;
    GameObject::reset();
}