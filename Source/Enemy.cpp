/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : Run Ai and attack the player*/


#include "CommonHeader.h"

Enemy::Enemy(int aMaxHealth, unsigned int aMeshIndex, ShaderProgramIndex aIndexShaderProgram, std::string aName) :
LivingObject(aMaxHealth, aIndexShaderProgram, aName),
m_EnemyState(EnemyStates_Patrolling),
m_MovementDuration(0),
m_MovementTimer(0),
m_TriggerDistanceSearchingOff(0),
m_TriggerDistanceSearchingOn(0),
m_PatrollingAngle(0),
m_PatrollingSpeed(0),
m_SearchingSpeed(0)
{
    //Set the mesh to use
    setMesh(GameFramework::getInstance()->getResourcesManager()->getMesh(aMeshIndex));
    m_AnimationTime=(float)ENEMY_DEFAULT_DEATH_ANIMATION_TIME;
}

Enemy::~Enemy()
{
}

void Enemy::update(double aDelta)
{
    if (m_Enabled == true && m_Alive==true)
    {
        Game* game = dynamic_cast<Game*>(GameFramework::getInstance()->getSceneManager()->getActiveScene());//Check if the active scene is the game

        if (game != nullptr)//if the game is active
        {
            Player* player = game->getPlayer();//Get the player

            if (player != nullptr)
            {
                //Get the palyer position
                Vector2 playerPosition = player->getPosition();

                switch (m_EnemyState)
                {
                case EnemyStates_Patrolling:
                    //Check if the player is close
                    if (checkTriggerOn(playerPosition) == true)
                    {
                        m_PatrollingAngle = getAngle();//Save the current angle as the patrolling angle
                        setAngle(getAngleBetween(playerPosition) + 180);//Set the angle of the enemy so that it moves toward the player
                        setState(EnemyStates_Searching);//Change the state to searching
                    }
                    else//Patrol
                    {
                        m_MovementTimer -= aDelta;//Reduce timer

                        if (m_MovementTimer <= 0)//If time is up
                        {
                            m_PatrollingAngle += 180;//Reverse the angle
                            setAngle(m_PatrollingAngle);
                            m_MovementTimer = m_MovementDuration;//Reset the timer
                        }
                    }
                    MoveGameObjectAngleSpeed(aDelta);//Move
                    break;

                case EnemyStates_Searching:
                    //Check if the player is now off range
                    if (checkTriggerOff(playerPosition) == true)
                    {
                        setState(EnemyStates_Patrolling);//Set the enemy to be patrolling
                    }
                    else if (checkTriggerOn(playerPosition) == true)//Update the direction in which the player is
                    {
                        setAngle(getAngleBetween(playerPosition) + 180);//Set the angle of the enemy so that it moves toward the player
                    }

                    MoveGameObjectAngleSpeed(aDelta);//Move
                    break;
                case EnemyStates_Dead:
                    break;
                default:
                    break;
                }
            }
        }

        boundsCollisionActiveScene();//Collide against map
    }

    LivingObject::update(aDelta);
}


void Enemy::setEnemy(float aPatrollingSpeed, float aSearchingSpeed, double aMovementDuratino, float aDirectionAngle, float aTriggerOnDistance, float aTriggerOffDistance)
{
    //Choose on which direction the enemy will head, it will head to either that direction or the opposite of it.
    //This is to create randomness and prevent all enemies from moving in the same direction
    unsigned int possibleDirection = 0 + (std::rand() % (1 - 0 + 1)); //Get a random number between 0 and 1
    if (possibleDirection == 0)
    {
        setAngle(aDirectionAngle);//Set direction normally
    }
    else
    {
        setAngle(aDirectionAngle + 180);//Go to the opposite direction
    }

    //After the angle has been set, save it for when it goes back to patrolling
    m_PatrollingAngle = getAngle();

    //Set the movement duration, and the timer
    m_MovementDuration = aMovementDuratino;
    m_MovementTimer = m_MovementDuration;

    //Set the trigger distances
    m_TriggerDistanceSearchingOn = aTriggerOnDistance;//Distance from which player will start searching
    m_TriggerDistanceSearchingOff = aTriggerOffDistance;//Distance where player will stop searching

    //Set the speeds
    m_PatrollingSpeed = aPatrollingSpeed;
    m_SearchingSpeed = aSearchingSpeed;

    m_Speed = m_PatrollingSpeed;
}

void Enemy::reset()
{
    //Reset the time
    m_MovementTimer = m_MovementDuration;

    //Set state back to patrolling
    setState(EnemyStates_Patrolling);

    LivingObject::reset();
}

bool Enemy::checkTriggerOn(Vector2 aTriggerPosition)
{

    //Check if the trigger is close
    if (m_TriggerDistanceSearchingOn >= calculateDistanceBetween(aTriggerPosition))
    {
        return true;//return the trigger is close
    }

    return false;//Return the trigger isn't close
}


bool Enemy::checkTriggerOff(Vector2 aTriggerPosition)
{

    //Check if the trigger is away
    if (m_TriggerDistanceSearchingOff <= calculateDistanceBetween(aTriggerPosition))
    {
        return true;//return the triggerr is away
    }

    return false;//Return the trigger is close

}

void Enemy::setState(EnemyStates aState)
{
    m_EnemyState = aState;//Set the state

    //Set the variables for each state
    switch (m_EnemyState)
    {
    case EnemyStates_Patrolling:
        setAngle(m_PatrollingAngle);//Set back its normal patrolling angle
        setSpeed(m_PatrollingSpeed);
        break;

    case EnemyStates_Searching:
        //No angle set because it is calculated according to player position
        setSpeed(m_SearchingSpeed);
        break;

    case EnemyStates_Dead:
        break;
    default:
        break;
    }



}