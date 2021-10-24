#ifndef __ENEMY__H__
#define __ENEMY__H__

const double ENEMY_DEFAULT_DEATH_ANIMATION_TIME = 2.0;

enum EnemyStates
{
    EnemyStates_Patrolling,
    EnemyStates_Searching,
    EnemyStates_Dead
};

/*Enemy class, it has basic AI of patrolling or if the enemy is near  charge him.*/
class Enemy :
    public LivingObject
{
public:
    Enemy(int maxHealth, unsigned int meshIndex, ShaderProgramIndex indexShaderProgram, std::string name);
    void setEnemy(float patrollingSpeed,float searchingSpeed, double movementDuratino, float directionAngle, float triggerOnDistance, float triggerOffDistance);  
    ~Enemy();

    virtual void update(double delta);

    virtual void setState(EnemyStates state);
    virtual void reset();

    bool checkTriggerOn(Vector2 triggerPosition);
    bool checkTriggerOff(Vector2 triggerPosition);

private:
    EnemyStates m_EnemyState;
    double m_MovementDuration;
    double m_MovementTimer;
    float m_TriggerDistanceSearchingOn;
    float m_TriggerDistanceSearchingOff;
    float m_PatrollingSpeed;
    float m_SearchingSpeed;
    float m_PatrollingAngle;
};

#endif