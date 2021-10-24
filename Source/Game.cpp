/*
Student:    Alvaro Chavez Mixco
Date:       Monday, October 19 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Run the main game logic. Create game objects, update them, draw them and delete them.

Modification history:
December 14 
-Made AI
-Game logic
-Power ups

*/

#include "CommonHeader.h"

using namespace std;

Game::Game() :Scene("Game"),
m_GameMainCamera(nullptr),
m_Player(nullptr),
m_ShieldIcon(nullptr),
m_TextEnemiesRemaining(nullptr),
m_ParticleSystem(nullptr),
m_EnemyEmitter(nullptr)
{
    m_GameMainCamera = new Camera(GAME_DEFAULT_PROJECTION_SCALE);//Create main camera
    setSceneSize(GAME_MAP_SIZE);//Set the size of the scene
}

Game::~Game()
{
    if (m_ParticleSystem != nullptr)
    {
        delete m_ParticleSystem;
        m_ParticleSystem = nullptr;
    }

}

void Game::loadContent()
{
    Vector2 sceneSize = getSceneSize();

    //Create the cameras
    addCamera(m_GameMainCamera);

    //HUD camera
    Camera* tempCamera = new Camera(HUD_CAMERA_PROJECTION_SCALE);
    tempCamera->setCameraPos(HUD_CAMERA_POSITION);//Set camera position to be 0
    addCamera(tempCamera);//HUD camera

    //Create background
    m_BackgroundRectangle = new RectangleObject(ShaderProgramIndex_Texture, sceneSize, GAME_BACKGROUND_TEXTURE_INDEX);//Scene background
    m_BackgroundRectangle->setPosition(sceneSize / 2);
    m_BackgroundRectangle->setScale(sceneSize);
    m_BackgroundRectangle->loadContent();

    //Create objects
    m_Player = new Player();
    m_Enemies = vector<GameObject*>(vector<GameObject*>(createEnemies(GAME_DEFAULT_NUMBER_OF_ENEMIES)));//Ideally object pooling would be done, but to avoid having to make a pool of enemies (and since
    //it is a small games), more enemies will be created as needed (they are not deleted at runtime).

    //Text
    m_TextEnemiesRemaining = new NumberFontSystem(0);
    m_TextEnemiesRemaining->setPosition(TEXT_NUMBER_ENEMIES__POSITION);
    m_TextEnemiesRemaining->setScale(TEXT_NUMBER_ENEMIES_DEFAULT_SCALE);

    //Shield icon
    m_ShieldIcon = new PowerUp(SHIELD_DURATION_TIME, SHIELD_COOLDOWN_TIME, SHIELD_DEPLETE_TIME, SHIELD_RECHARGE_TIME);
    m_ShieldIcon->setMesh(GameFramework::getInstance()->getResourcesManager()->getMesh(MESH_SHIELD_ICON_INDEX));//Set mesh for the shield icon
    m_ShieldIcon->setShaders(SHIELD_ICON_SHADER_EMPTY, SHIELD_ICON_SHADER_FULL, SHIELD_ICON_SHADER_ACTIVE, SHIELD_ICON_SHADER_DEPLETING, SHIELD_ICON_SHADER_RECHARGING);
    m_ShieldIcon->setColor(SHIELD_ICON_FRONT_COLOR);
    m_ShieldIcon->setBackColor(SHIELD_ICON_BACK_COLOR);
    m_ShieldIcon->setScale(SHIELD_ICON_DEFAULT_SCALE);
    m_ShieldIcon->setPosition(SHIELD_ICON_DEFAULT_POSITION);

    //Add objects to scene. The scene will update them and delete them from memory
    addGameObject(m_Player);
    addMultipleGameObjects(m_Enemies);
    addGameObject((GameObject*)m_TextEnemiesRemaining);
    addGameObject(m_ShieldIcon);

    //Add the objects to the camera
    //Game camera
    m_GameMainCamera->addObjectToDraw(m_Player);
    m_GameMainCamera->addMultipleObjectsToDraw(m_Enemies);

    //HUD camera
    tempCamera->addObjectToDraw(m_TextEnemiesRemaining);
    tempCamera->addObjectToDraw(m_ShieldIcon);

    //create player emitter
    ParticleEmitter* playerEmitter = nullptr;
    GLuint particleTexture=GameFramework::getInstance()->getResourcesManager()->getTexture(PARTICLE_TEXTURE_INDEX);
    m_ParticleSystem = new ParticleSystem(ShaderProgramIndex_VaryingColorTexture, particleTexture);

    //Set the emitter properties
    ParticleEmitter* tempEmitter = nullptr;
    m_ParticleSystem->createAddParticleEmitter(PLAYER_EMITTER_NUMBER_PARTICLES);
    tempEmitter = m_ParticleSystem->getParticleEmitter(0);
    tempEmitter->setFiringAngleRange(PLAYER_EMITTER_FIRING_ANGLE_RANGE);
    tempEmitter->setSpeedRange(PLAYER_EMITTER_SPEED_RANGE);
    tempEmitter->setAllParticles(PLAYER_PARTICLES_COLOR, PLAYER_PARTICLES_SIZE, PLAYER_PARTICLE_DEFAULT_DURATION);
    tempEmitter->setSize(PLAYER_EMITTER_SIZE);

    //Set this emitter as the players one
    m_Player->setEmmitter(tempEmitter);

    //Create another renderer to be activated when the enemy dies
    m_ParticleSystem->createAddParticleEmitter(ENEMY_DEAD_NUMBER_PARTICLES);
    m_EnemyEmitter = m_ParticleSystem->getParticleEmitter(1);
    m_EnemyEmitter->setFiringAngleRange(ENEMY_DEAD_EMITTER_FIRING_ANGLE_RANGE);
    m_EnemyEmitter->setSpeedRange(ENEMY_DEAD_EMITTER_SPEED_RANGE);
    m_EnemyEmitter->setAllParticles(PARTICLE_DEFAULT_COLOR, PARTICLE_DEFAULT_SIZE, PARTICLE_DEFAULT_DURATION);

    Scene::loadContent();
}

void Game::update(double aDelta)
{


    if (GameFramework::getInstance()->getInputManager()->getKeyState('R') == true)//Check if the user has pressed R
    {
        //Note: I could probably do something so that the program only reads 1 key presses, but by reading a keypress multiple times, it creates a nice effect of completely randomly 
        //selecting a level.
        reset();//Restart the level
    }

    //Done in here since its not really a powerup , but a part of the Game hid
    if (GameFramework::getInstance()->getInputManager()->getKeyState('Q') == true)//Check if the user has pressed R
    {
        m_ShieldIcon->setStatus(PowerUpStatus_Active);//Activate power up

        //If the power up was activated, change the shader of palyer
        if (m_ShieldIcon->getPowerUpActive() == true)
        {
            m_Player->useDeathAnimationShader();//Not death, but Invincibility, reusing variable
        }
    }

    m_GameMainCamera->followObject(m_Player, aDelta);//Make the camera follow the player

    unsigned int currentNumEnemies = 0;//Current number of enemies in this update

    //Collision
    if (m_Player != nullptr)
    {
        //If player is alive handle collision
        if (m_Player->getAlive() == true)
        {
          
            
            Enemy* tempEnemy = nullptr;

            //REALLY INNEFECTIVE MEHTOD FOR COLLISION
            //Check for player collision against all the enemies
            for (unsigned int i = 0; i < m_Enemies.size(); i++)
            {
                if (m_Enemies.at(i) != nullptr)//if the enemy is valid
                {
                    tempEnemy = dynamic_cast<Enemy*>(m_Enemies.at(i));//Check that it is type enemy

                    //If it is an enemy
                    if (tempEnemy != nullptr)
                    {
                        if (tempEnemy->getAlive() == true)//Only check collision if enemy is alive
                        {
                            //If the enemy collided with the player
                            if (m_Player->circleCollisionCheck(tempEnemy) == true)//If there is a collision
                            {
                                if (m_ShieldIcon->getPowerUpActive() == false)//Only apply damage if the power up is not active 
                                {
                                    m_Player->applyDamage(tempEnemy->getCollisionDamage());///Damage the player
                                }
                            }

                            //Collision against the projectiles (NOT AN EFFICIENT WAY TO DO COLLISION)
                            vector<Projectile*> playerProjectiles = m_Player->getPlayerActiveProjectiles();

                            //Go through all the projectiles
                            for (unsigned int j = 0; j < playerProjectiles.size(); j++)
                            {

                                if (playerProjectiles.at(j) != nullptr)
                                {
                                    //Check if the projectile collided with the enemy
                                    if (playerProjectiles.at(j)->circleCollisionCheck(tempEnemy))
                                    {
                                        tempEnemy->applyDamage(playerProjectiles.at(j)->getAttackDamage());//Apply damage to enemy according to projectile
                                        playerProjectiles.at(j)->deactivateProjectile();//Deactivate projectile

                                        if (tempEnemy->getAlive() == false)
                                        {
                                            //Move emitter to enemy position
                                            m_EnemyEmitter->setEmitterPosition(tempEnemy->getPosition());
                                            m_EnemyEmitter->setSize(tempEnemy->getRadius() * 2);
                                            m_EnemyEmitter->fireParticles(ENEMY_DEAD_PARTICLES_TO_FIRE, tempEnemy->getAngle(), ENEMY_DEAD_PARTICLES_SPEED);
                                        }
                                    }
                                }
                            }

                            if (tempEnemy->getAlive() == true)
                            {
                                currentNumEnemies++;//Update the enemy count
                            }

                        }//End of if (tempEnemy->getAlive() == true)
                    }//end of (tempEnemy != nullptr)
                }//End of if (m_Enemies.at(i) != nullptr)
            }//End of for (unsigned int i = 0; i < m_Enemies.size(); i++)


        }

        //Check if the player is dead, after the collision checks
        if (m_Player->getAlive() == false)
        {
            reset();
        }

        if (currentNumEnemies <= 0)//iF all enemies have been killed
        {
            reset();
        }

        //Set the enemy count
        m_TextEnemiesRemaining->setNumber(currentNumEnemies);
    }


    m_ParticleSystem->update(aDelta);

    Scene::update(aDelta);
}

void Game::draw()
{
    Scene::draw();
    m_ParticleSystem->draw(m_GameMainCamera->getPosition(), m_GameMainCamera->getProjectionScale());
}

void Game::reset()
{
    //Dont reset, it is a nice effect to see camera move
    //m_GameMainCamera->setCameraPos(m_Player->getPosition());//Set the camera to be the player positio

    //Place all the enemies randomly
    for (unsigned int i = 0; i < m_Enemies.size(); i++)
    {
        Enemy* tempEnemy = dynamic_cast<Enemy*>(m_Enemies.at(i));//Ensure that it is an enemy

        if (m_Enemies.at(i) != nullptr)
        {
            randomlyPlaceEnemy(tempEnemy);//Place the enemy
        }
    }

    Scene::reset();
}

void Game::onSurfaceChanged()
{
    //Set the viewport for all the cameras
    Vector2 windowSize = GameFramework::getInstance()->getWindowSize();


    Camera* tempCamera = getCameraAtIndex(1);//Get the hud camemra
    tempCamera->setViewportSettings(Vector2(0, 0), windowSize);
    m_GameMainCamera->setViewportSettings(Vector2(0, 0), windowSize);

}

//Returns a vector of game objects since that way they are easier to manage
vector<GameObject*> Game::createEnemies(unsigned int aNumEnemies)
{

    vector<GameObject*> enemiesAdded;//The vector of enemies that will be returned, it will contain all the enemies created
    unsigned int enemyType = 0;//Number to determine the enemy type
    Enemy* tempEnemy = nullptr;

    for (unsigned int i = 0; i < aNumEnemies; i++)
    {

        //Choose the type of enemy that will appear
        enemyType = 0 + (std::rand() % (GAME_ENEMY_NUMBER_OF_TYPES - 0)); //Get a random number between 0 and THE NUMBER OF ENEMIES

        switch (enemyType)
        {

        case 0://Enemy normal
            tempEnemy = new Enemy(ENEMY_NORMAL_MAX_HEALTH, MESH_ENEMY_NORMAL_INDEX, ENEMY_NORMAL_DEFAULT_SHADER_INDEX, ENEMY_NORMAL_NAME);//Create enemy
            tempEnemy->setEnemy(ENEMY_NORMAL_PATROLLING_SPEED, ENEMY_NORMAL_SEARCHING_SPEED, ENEMY_NORMAL_MOVEMENT_DURATION, ENEMY_NORMAL_DEFAULT_ANGLE,
                ENEMY_NORMAL_TRIGGER_ON_DISTANCE, ENEMY_NORMAL_TRIGGER_OFF_DISTANCE);               //Set the properties of the enemy
            tempEnemy->setColor(ENEMY_NORMAL_OBJECT_COLOR);//Set the color of the enemy
            tempEnemy->setCollisionDamage(ENEMY_NORMAL_COLLISION_DAMAGE);//Set collision damage
            enemiesAdded.push_back((GameObject*)tempEnemy);//Add enemy to vector
            break;


        case 1://Enemy big
            tempEnemy = new Enemy(ENEMY_BIG_MAX_HEALTH, MESH_ENEMY_BIG_INDEX, ENEMY_BIG_DEFAULT_SHADER_INDEX, ENEMY_BIG_NAME);//Create enemy
            tempEnemy->setEnemy(ENEMY_BIG_PATROLLING_SPEED, ENEMY_BIG_SEARCHING_SPEED, ENEMY_BIG_MOVEMENT_DURATION, ENEMY_BIG_DEFAULT_ANGLE,
                ENEMY_BIG_TRIGGER_ON_DISTANCE, ENEMY_BIG_TRIGGER_OFF_DISTANCE);               //Set the properties of the enemy
            tempEnemy->setColor(ENEMY_BIG_OBJECT_COLOR);//Set the color of the enemy
            tempEnemy->setCollisionDamage(ENEMY_BIG_COLLISION_DAMAGE);//Set collision damage
            enemiesAdded.push_back((GameObject*)tempEnemy);//Add enemy to vector
            break;

        default:
            break;
        }
    }

    return enemiesAdded;//Return all the enemies that were created    

}

void Game::randomlyPlaceEnemy(Enemy* aEnemy)
{
    float randomX = 0;
    float randomY = 0;
    float enemyRadius = 0;

    if (aEnemy != nullptr)
    {

        //Get a random x and y value
        randomX = rand() % (unsigned int)(GAME_MAP_SIZE.x - enemyRadius) + enemyRadius;
        randomY = rand() % (unsigned int)(GAME_MAP_SIZE.y - enemyRadius) + enemyRadius;

        //Checks that the enemy isn't placed in the player spawn safe areas 
        if (randomX < ENEMY_SPAWN_SAFE_AREA && randomY < 0 + ENEMY_SPAWN_SAFE_AREA) //Check top left (player)
        {

            randomlyPlaceEnemy(aEnemy);//Recursion if the enemy is on player's or target's safe zones
        }
        else
        {
            aEnemy->setPosition(Vector2(randomX, randomY));//Set the nemy position
        }

    }
}