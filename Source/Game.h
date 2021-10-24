#ifndef __GAME__H__
#define __GAME__H__

#include <vector>
#include "Framework/base/Scene.h"
#include "Framework/base/Camera.h"

const Vector2 GAME_DEFAULT_PROJECTION_SCALE = Vector2(100.0f, 100.0f);
const Vector2 GAME_MAP_SIZE = Vector2(400.0f, 400.0f);

const unsigned int GAME_DEFAULT_NUMBER_OF_ENEMIES = 20;
const unsigned int ENEMY_SPAWN_SAFE_AREA = 100;//The space (width and height) in which enemies won't be placed

//HUD Camera projection scale
const Vector2 HUD_CAMERA_PROJECTION_SCALE = Vector2(10, 10);
const Vector2 HUD_CAMERA_POSITION = Vector2(10, 10);

//Font system
const Vector2 TEXT_NUMBER_ENEMIES_DEFAULT_SCALE = Vector2(2.0f, 1.0f);
const Vector2 TEXT_NUMBER_ENEMIES__POSITION = Vector2(2, 2);

//Shield properties
const Vector2 SHIELD_ICON_DEFAULT_SCALE = Vector2(2.0f, 2.0f);//25
const Vector2 SHIELD_ICON_DEFAULT_POSITION = Vector2(2.5f, 5.0f);
const double SHIELD_DURATION_TIME = 5.0;
const double SHIELD_COOLDOWN_TIME = 5.0;
const double SHIELD_DEPLETE_TIME = 2.0;
const double SHIELD_RECHARGE_TIME = 1.0;
const Vector4Int SHIELD_ICON_FRONT_COLOR = Vector4Int(75, 0, 130, 255);
const Vector4Int SHIELD_ICON_BACK_COLOR = Vector4Int(200, 20, 20, 255);
const ShaderProgramIndex SHIELD_ICON_SHADER_FULL = ShaderProgramIndex_FragColor;
const ShaderProgramIndex SHIELD_ICON_SHADER_EMPTY = ShaderProgramIndex_FragBackColor;
const ShaderProgramIndex SHIELD_ICON_SHADER_ACTIVE = ShaderProgramIndex_VaryingColorEffect;
const ShaderProgramIndex SHIELD_ICON_SHADER_DEPLETING = ShaderProgramIndex_VeticalFillOutAnimation;
const ShaderProgramIndex SHIELD_ICON_SHADER_RECHARGING = ShaderProgramIndex_VeticalFillInAnimation;

//Enemies properties
const unsigned int GAME_ENEMY_NUMBER_OF_TYPES = 2;

const unsigned int ENEMY_NORMAL_MAX_HEALTH = 1;
const ShaderProgramIndex ENEMY_NORMAL_DEFAULT_SHADER_INDEX = ShaderProgramIndex_VaryingColor;
const float ENEMY_NORMAL_DEFAULT_ANGLE = 180;
const Vector4Int ENEMY_NORMAL_OBJECT_COLOR = Vector4Int(170, 255, 170, 255);//Not currently used in shader
const float ENEMY_NORMAL_PATROLLING_SPEED = 10.0F;
const float ENEMY_NORMAL_SEARCHING_SPEED = 20.0f;
const float ENEMY_NORMAL_TRIGGER_ON_DISTANCE = 70.0f;
const float ENEMY_NORMAL_TRIGGER_OFF_DISTANCE = 80.0f;
const double ENEMY_NORMAL_MOVEMENT_DURATION = 5.0;
const int ENEMY_NORMAL_COLLISION_DAMAGE = 1;
const std::string ENEMY_NORMAL_NAME = "EnemyNormal";

const unsigned int ENEMY_BIG_MAX_HEALTH = 3;
const ShaderProgramIndex ENEMY_BIG_DEFAULT_SHADER_INDEX = ShaderProgramIndex_FragColor;
const float ENEMY_BIG_DEFAULT_ANGLE = 90;
const Vector4Int ENEMY_BIG_OBJECT_COLOR = Vector4Int(200, 50, 120, 255);
const float ENEMY_BIG_PATROLLING_SPEED = 7.5f;
const float ENEMY_BIG_SEARCHING_SPEED = 15.0f;
const float ENEMY_BIG_TRIGGER_ON_DISTANCE = 50.0f;
const float ENEMY_BIG_TRIGGER_OFF_DISTANCE = 60.0f;
const int ENEMY_BIG_COLLISION_DAMAGE = 2;
const double ENEMY_BIG_MOVEMENT_DURATION = 2;

const float ENEMY_DEAD_EMITTER_SPEED_RANGE = 4;
const float ENEMY_DEAD_EMITTER_FIRING_ANGLE_RANGE = 360;
const unsigned int ENEMY_DEAD_NUMBER_PARTICLES = 1000;
const unsigned int ENEMY_DEAD_PARTICLES_TO_FIRE = 100;
const float ENEMY_DEAD_PARTICLES_SPEED = 10;

const std::string ENEMY_BIG_NAME = "EnemyBig";

class Player;
class Enemy;
class GameObject;
class PowerUp;

/*This class contains all the game objects and the main game logic of the game*/
class Game: public Scene
{
public:
    Game();
    virtual ~Game();

	virtual void update(double delta);
	virtual void draw();
	virtual void loadContent();
	virtual void reset();
    virtual void onSurfaceChanged();

    Player* getPlayer(){ return m_Player; }

    std::vector<GameObject*> createEnemies(unsigned int numEnemies);//Returns a vector of game objects since that way they are easier to manage
    void randomlyPlaceEnemy(Enemy*eEnemy);

    Camera* getMainGameCamera(){ return m_GameMainCamera; }

    ParticleSystem* getParticleSystem(){ return m_ParticleSystem; }

private:

    Camera* m_GameMainCamera;

    Player* m_Player;
    std::vector<GameObject*> m_Enemies;//Store in a variable because they are constantly being randomly placed, but not as enemies so that it can easily interact with scene

    NumberFontSystem* m_TextEnemiesRemaining;
    PowerUp* m_ShieldIcon;

    ParticleSystem* m_ParticleSystem;
    ParticleEmitter* m_EnemyEmitter;//Deleted by particle system
};


#endif //__Game_H__