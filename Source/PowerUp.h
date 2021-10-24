#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Framework/Base/GameObject.h"

enum PowerUpStatus
{
    PowerUpStatus_Empty,
    PowerUpStatus_Full,
    PowerUpStatus_Active,
    PowerUpStatus_Depleting,
    PowerUpStatus_Recharging
};

/*More than an actual powerup, this is more an icon power up class. Used to set the different states while charging a powerup*/
class PowerUp : public GameObject
{
public:
    PowerUp(double durationTime, double cooldownTime,double depleteTime, double rechargeTime);
    ~PowerUp();
    
    void setTimers(double durationTime, double cooldownTime, double depleteTime, double rechargeTime);
    void setShaders(ShaderProgramIndex shaderFull, ShaderProgramIndex shaderEmpty, ShaderProgramIndex shaderActive, ShaderProgramIndex shaderDepleting, ShaderProgramIndex shaderRecharging);

    PowerUpStatus getStatus(){ return m_Status; }
    void setStatus(PowerUpStatus status);

    bool getPowerUpActive(){ return m_PowerUpActive; }

    virtual void update(double delta);
    virtual void reset();

private:
    PowerUpStatus m_Status;

    ShaderProgramIndex m_ShaderFull;
    ShaderProgramIndex m_ShaderEmpty;
    ShaderProgramIndex m_ShaderActive;
    ShaderProgramIndex m_ShaderDepleting; 
    ShaderProgramIndex m_ShaderRecharging;

    //Made into variables so game could potentially change values
    double m_DurationTime;
    double m_CooldownTIme;
    double m_DepleteTime;
    double m_RechargeTime;

    bool m_PowerUpActive;
    bool m_PowerUpAvailable;
};


#endif