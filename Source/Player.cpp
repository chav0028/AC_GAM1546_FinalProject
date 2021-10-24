/*
Student:    Alvaro Chavez Mixco
Date:       Monday, October 19 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Set the properties of the player. Handle keyboard input and movement of the player.

October 3:
-Added a Alive bool status for Player.
-Added a HandleKeyEvents method in Player, this will check for arrow keys or WASD input and move the player accordingly.

October 4:
-Separate in Player.cpp the EnemyCollision and TargetCollision methods, these will be called in Game.cpp Update.

October 12:
-Make EnemyCollision on Player return a bool.
-Made the Reset function in Player so that it resets the player position and alive status.

October 18:
-Removed drawPlayerShape function, since the player per the assignment description has to be a circle.

*/

#include "CommonHeader.h"

using namespace std;

Player::Player() :LivingObject(PLAYER_DEFAULT_HEALTH, PLAYER_DEFAULT_SHADER, "Player"),
m_ProjectilePool(PLAYER_NUMBER_PROJECTILES),
m_CanFire(true),
m_CooldownTimer(PLAYER_PROJECTILE_COOLDOWN),
m_Emitter(nullptr)
{
	//Set variables
	m_Enabled = true;
	m_Color = PLAYER_COLOR;
	m_Speed = PLAYER_SPEED;
    m_Position = PLAYER_DEFAULT_POSITION;
    m_IndexTextureToUse = PLAYER_TEXTURE_INDEX;//Texture
    m_RegularShader = PLAYER_DEFAULT_SHADER;
    m_AnimationTime = (float)PLAYER_INVINCIBLE_ANIMATION_TIME;
    m_DeathAnimationShader = PLAYER_INVINCIBLE_SHADER;//Not really death animation, just activated when player is invincible
}

Player::~Player()
{
}

void Player::loadContent()
{
    //Get mesh
    setMesh(GameFramework::getInstance()->getResourcesManager()->getMesh(MESH_PLAYER_INDEX));

    setScale(PLAYER_DEFAULT_SCALE);//Set the player scale    

}

void Player::update(double aDelta)
{
    if (m_CanFire == false)//If there is currently a cooldown
    {
        m_CooldownTimer -= aDelta;//reduce the timer

        if (m_CooldownTimer <= 0)//if timer is over
        {
            m_CanFire = true;//Plaer can shoot
            m_CooldownTimer = PLAYER_PROJECTILE_COOLDOWN;
        }
    }

    //if the user is invincible
    if (m_IndexShaderProgramToUse == m_DeathAnimationShader)
    {
        m_AnimationTimer -= aDelta;//Substract to time

        if (m_AnimationTimer <= 0)//if time is up
        {
            m_AnimationTimer = m_AnimationTime;//Reset timer
            m_IndexShaderProgramToUse = m_RegularShader;//use normal shader
        }
    }

    LivingObject::update(aDelta);

    if (m_Enabled == true)
    {
        //If active , set the emitter
        if (m_Emitter != nullptr)
        {
            m_Emitter->setEmitterPosition(m_Position);//sets its position to match the player

        }

        handleKeyEvents(aDelta);//User input (movement)
        boundsCollisionActiveScene();//Player-map bounds check
        //Enemy and Target collision are done in Game (functions are in here) so that we can use the bool returned in them to check different conditions.
    }

    //Update all the active projectiles
    vector<Projectile*> activeProjectiles = getPlayerActiveProjectiles();
    for (unsigned int i = 0; i < activeProjectiles.size(); i++)
    {
        if (activeProjectiles.at(i) != nullptr)
        {
            activeProjectiles.at(i)->update(aDelta);
        }
    }

}

void Player::draw(Vector2 aCameraPosition, Vector2 aProjectionScale)
{
    if (m_Enabled == true)
    {
        GameObject::draw(aCameraPosition, aProjectionScale);
    }

    //Draw all the active projectiles
    vector<Projectile*> activeProjectiles = getPlayerActiveProjectiles();
    for (unsigned int i = 0; i < activeProjectiles.size(); i++)
    {
        if (activeProjectiles.at(i) != nullptr)
        {
            activeProjectiles.at(i)->draw(aCameraPosition,aProjectionScale);
        }
    }
}

//Processes keyboard input
void Player::handleKeyEvents(double aDelta)
{
	InputManager* inputManager=GameFramework::getInstance()->getInputManager();
	
	//Horizontal movement
	if (inputManager->getKeyState(VK_RIGHT) || inputManager->getKeyState('D'))//Right key or D is Pressed
	{
		setAngle(getAngle()- (float)aDelta*PLAYER_ROTATION_SPEED);//Rotate the player to the right
	}
	//Use else if, instead of only if so that the player can't press both at the same tiem
	else if (inputManager->getKeyState(VK_LEFT) || inputManager->getKeyState('A'))//Left key or A is pressed
	{
		setAngle(getAngle() + (float)aDelta*PLAYER_ROTATION_SPEED);//Rotate the player to the left
	}

	//Vertical and Horizontal movement are in differen else if... statements so that player can do both at the same time

	//Vertical movement
	if (inputManager->getKeyState(VK_DOWN) || inputManager->getKeyState('S'))//Down key or S is Pressed
	{
		MoveGameObjectAngleSpeed(aDelta, false);//Move backward
	}
	else if (inputManager->getKeyState(VK_UP) || inputManager->getKeyState('W'))//Up key or W is pressed
	{
		MoveGameObjectAngleSpeed(aDelta, true);//Move forkward
        m_Emitter->fireParticles(PLAYER_EMITTER_PARTICLES_TO_FIRE, getAngle() + 180, PLAYER_EMITTER_SPEED_RANGE);

	}

    if (inputManager->getKeyState(VK_SPACE)==true)//SPace is pressed
    {
        fireProjectile();
    }

}

void Player::reset()
{
	m_Enabled = true;//Say the player is alive
    m_Position = PLAYER_DEFAULT_POSITION;//Set it to its default position
    if (m_Emitter != nullptr)
    {
        m_Emitter->setEmitterPosition(PLAYER_DEFAULT_POSITION);//Reset the emitter
    }

    //Reset the projectiles
    vector <Projectile*> activeProjectiles = m_ProjectilePool.getCurrentlyActiveObjects();
    for (unsigned int i = 0; i < activeProjectiles.size(); i++)
    {
        if (activeProjectiles.at(i) != nullptr)
        {
            activeProjectiles.at(i)->deactivateProjectile();
        }
    }

    LivingObject::reset();
}

void Player::fireProjectile()
{
    Projectile* activeProjectile = m_ProjectilePool.getActivateObject();//Get and activate a projectile
    if (activeProjectile != nullptr)
    {
        if (m_CanFire == true)
        {
            activeProjectile->fire(PLAYER_PROJECTILE_DURATION, getAngle(), getPosition(), PLAYER_PROJECTILE_SPEED, PLAYER_PROJECTILE_ATTACK_DAMAGE);//Fire the projectile
            m_CanFire = false;//Activate cooldown
        }
    }
}