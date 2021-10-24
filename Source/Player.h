#ifndef __PLAYER_H__
#define __PLAYER_H__

const ShaderProgramIndex PLAYER_DEFAULT_SHADER = ShaderProgramIndex_Texture;
const ShaderProgramIndex PLAYER_INVINCIBLE_SHADER = ShaderProgramIndex_FragmentEffect;
const Vector2 PLAYER_DEFAULT_POSITION = Vector2(0.0f, 0.0f);
const float PLAYER_SPEED = 40.0f;
const Vector4Int PLAYER_COLOR = Vector4Int(255, 05, 255, 255);
const float PLAYER_ROTATION_SPEED = 500.0f;
const int PLAYER_DEFAULT_HEALTH = 3;
const float PLAYER_DEFAULT_SCALE = 1.0f;
const double PLAYER_INVINCIBLE_ANIMATION_TIME = SHIELD_DURATION_TIME;

const double PLAYER_PROJECTILE_COOLDOWN = 0.3;
const unsigned int PLAYER_NUMBER_PROJECTILES = 150;
const float PLAYER_PROJECTILE_SPEED = 50.0f;
const int PLAYER_PROJECTILE_ATTACK_DAMAGE = 1;
const double PLAYER_PROJECTILE_DURATION = 5.0;

const unsigned int PLAYER_EMITTER_NUMBER_PARTICLES = 300;
const unsigned int PLAYER_EMITTER_PARTICLES_TO_FIRE = 1;
const float PLAYER_EMITTER_FIRING_ANGLE_RANGE = 120;
const float PLAYER_EMITTER_SPEED_RANGE = 2;
const double PLAYER_PARTICLE_DEFAULT_DURATION = 0.6;
const Vector2 PLAYER_EMITTER_SIZE(5.0f, 1.0f);
const Vector4Int PLAYER_PARTICLES_COLOR = Vector4Int(0, 250, 255, 255);
const Vector2 PLAYER_PARTICLES_SIZE(2.0f, 2.0f);

class Projectile;

/*The p[layer class, this class handles the main input from the player.*/
class Player : public LivingObject
{

public:
    Player();
    virtual ~Player();

    void loadContent();

    virtual void update(double delta);
    virtual void draw(Vector2 cameraPosition, Vector2 projectionScale);
    void handleKeyEvents(double delta);
    void reset();

    void fireProjectile();

    void setEmmitter(ParticleEmitter* aEmitter){ m_Emitter = aEmitter; }


    std::vector<Projectile*> getPlayerActiveProjectiles(){ return m_ProjectilePool.getCurrentlyActiveObjects(); }

private:
    //Projectiles object pooling
    Pool<Projectile> m_ProjectilePool;

    bool m_CanFire;
    double m_CooldownTimer;
    ParticleEmitter* m_Emitter;
};
#endif //__Game_H__