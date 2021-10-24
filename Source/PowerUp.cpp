/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose :Run timers for the different states a power uo has,*/


#include "CommonHeader.h"

PowerUp::PowerUp(double aDurationTime, double aCooldownTime, double aDepleteTime, double aRechargeTime) :GameObject(ShaderProgramIndex_VaryingColor, "PowerUp"),
m_DepleteTime(aDepleteTime),
m_DurationTime(aDurationTime),
m_RechargeTime(aRechargeTime),
m_CooldownTIme(aCooldownTime),
m_ShaderActive(ShaderProgramIndex_VaryingColor),
m_ShaderDepleting(ShaderProgramIndex_VaryingColor),
m_ShaderEmpty(ShaderProgramIndex_VaryingColor),
m_ShaderRecharging(ShaderProgramIndex_VaryingColor),
m_ShaderFull(ShaderProgramIndex_VaryingColor),
m_Status(PowerUpStatus_Full),
m_PowerUpActive(false),
m_PowerUpAvailable(true)
{
}


PowerUp::~PowerUp()
{
}

void PowerUp::setTimers(double aDurationTime, double aCooldownTime, double aDepleteTime, double aRechargeTime)
{
    m_DurationTime = aDurationTime;
    m_CooldownTIme = aCooldownTime;
    m_DepleteTime = aDepleteTime;
    m_RechargeTime = aRechargeTime;
}

void PowerUp::setShaders(ShaderProgramIndex aShaderEmpty, ShaderProgramIndex aShaderFull, ShaderProgramIndex aShaderActive, ShaderProgramIndex aShaderDepleting, ShaderProgramIndex aShaderRecharging)
{
    m_ShaderEmpty = aShaderEmpty;
    m_ShaderFull = aShaderFull;
    m_ShaderActive = aShaderActive;
    m_ShaderDepleting = aShaderDepleting;
    m_ShaderRecharging = aShaderRecharging;
}

void PowerUp::update(double aDelta)
{

    switch (m_Status)
    {
    case PowerUpStatus_Full:
        //Do nothing
        break;

    case PowerUpStatus_Empty:
        m_AnimationTimer -= aDelta;

        if (m_AnimationTimer <= 0)
        {
            setStatus(PowerUpStatus_Recharging);//Set the power up to be recharging
        }
        break;

    case PowerUpStatus_Active:
        m_AnimationTimer -= aDelta;//Reduce the duration time

        if (m_AnimationTimer <= 0)//If time over
        {
            m_PowerUpActive = false;//set as inactive
            m_PowerUpAvailable = false;//Set that the power up can't be used
            setStatus(PowerUpStatus_Depleting);//Set the power up to be depleting
        }
        break;

    case PowerUpStatus_Depleting:
        m_AnimationTimer -= aDelta;//Reduce the duration time
        if (m_AnimationTimer <= 0)//If time over
        {
            setStatus(PowerUpStatus_Empty);//Set the power up to be empty
        }
        break;

    case PowerUpStatus_Recharging:
        m_AnimationTimer -= aDelta;//Increase time
        if (m_AnimationTimer <= 0)//If it reaches the full itme
        {
            setStatus(PowerUpStatus_Full);//Set the power up to be full
        }
        break;

    default:
        break;
    }
}



void PowerUp::setStatus(PowerUpStatus aStatus)
{

    //Set all the varaibles according to the status
    //Time
    //Shader
    //etc
    switch (aStatus)
    {
    case PowerUpStatus_Empty:
        m_AnimationTimer = m_CooldownTIme;
        m_IndexShaderProgramToUse = m_ShaderEmpty;
        break;

    case PowerUpStatus_Full:
        m_IndexShaderProgramToUse = m_ShaderFull;
        m_PowerUpAvailable = true;//Set the power up is available
        break;

    case PowerUpStatus_Active:
        if (m_PowerUpAvailable == true)//if the power up can be used
        {
            m_AnimationTimer = m_DurationTime;
            m_IndexShaderProgramToUse = m_ShaderActive;
            m_PowerUpActive = true;
        }

        break;

    case PowerUpStatus_Depleting:
        m_AnimationTimer = m_DepleteTime;
        m_IndexShaderProgramToUse = m_ShaderDepleting;
        break;

    case PowerUpStatus_Recharging:
        m_AnimationTimer = m_RechargeTime;
        m_IndexShaderProgramToUse = m_ShaderRecharging;
        break;

    default:
        break;
    }

    m_AnimationTime = m_AnimationTimer;//Set the animation time as the current value in the time in case we need to make extra animations with it
    m_Status = aStatus;
}

void PowerUp::reset()
{
    setStatus(PowerUpStatus_Full);
    GameObject::reset();
}