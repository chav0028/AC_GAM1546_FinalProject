#ifndef __GAMEOBJECT__H__
#define __GAMEOBJECT__H__

#include <vector>
#include <string>

const float GAMEOBJECT_DEFAULT_ANGLE = 0;

class Scene;
class Mesh;
class Texture;

/*Base class that contains the different properties a gameobject an have*/
class GameObject
{
public:
    GameObject(ShaderProgramIndex indexShaderProgram, std::string name);
    ~GameObject();

    virtual void loadContent();
    virtual void update(double delta);
    virtual void draw(Vector2 cameraPosition, Vector2 projectionScale);
    virtual void reset();

	virtual  void MoveGameObjectAngleSpeed(double delta,bool moveForward=true);

	//Collision detection methods
	virtual bool circleCollisionCheck(GameObject *object);
	float calculateDistanceBetween(Vector2 position);
	bool boundsCollisionActiveScene();
    float getAngleBetween(Vector2 aPosition);

	//Getters and setters
    bool getEnabled(){ return m_Enabled; }
    void setEnabled(bool aEnabledStatus){ m_Enabled = aEnabledStatus; }

    Vector2 getPosition(){ return m_Position; }
    void setPosition(Vector2 aPosition){ m_Position = aPosition; }

    Vector2 getScale(){ return m_Scale; }
    void setScale(Vector2 aScale);

    void setAngle(float angle);
    float getAngle();

    float getRadius();

    void setColor(Vector4Int aColor) { m_Color = aColor; }
    Vector4Int getColor() { return m_Color; }

    void setBackColor(Vector4Int aColor) { m_BackColor = aColor; }
    Vector4Int getBackColor() { return m_BackColor; }

    void setIndexShaderProgramToUse(ShaderProgramIndex aIndex) { m_IndexShaderProgramToUse = aIndex; }
    ShaderProgramIndex getIndexShaderProgramToUse() { return m_IndexShaderProgramToUse; }

    double getAnimationTimer(){ return m_AnimationTimer; }

    unsigned int getIndexTextureToUse() { return m_IndexTextureToUse; }
    
    void setSpeed(float aSpeed){ m_Speed = aSpeed; }
    float getSpeed(){ return m_Speed; }

    Vector2 getUVOffset(){ return m_UVOffset; }
    void setUVoffset(Vector2 aOffset){ m_UVOffset = aOffset; }

    Vector2 getUVScale(){ return m_UVScale; }
    void setUVScale(Vector2 aScale){ m_UVScale = aScale; }

    void setMesh(Mesh* mesh);

    float getAnimationTime(){ return m_AnimationTime; }
    void setAnimationTime(float aTime){ m_AnimationTime = aTime; }

protected:
    bool m_Enabled;
    Vector2 m_Position;

    float m_Speed;

	Vector4Int	m_Color;//Made into a variable (rather than relying only in vertex attribute) so that the color of an object can be manipulated easier in fragment shader.
    Vector4Int m_BackColor;
    Vector2 m_UVOffset;
    Vector2 m_UVScale;

    unsigned int m_IndexTextureToUse;
    double m_AnimationTimer;

    ShaderProgramIndex m_IndexShaderProgramToUse;//The index of which shader program will be used to draw an object
    std::string m_GameObjectName;

    float m_AnimationTime;
   
private://Private variables in case the setter does some special type of check
    void setRadiusMeshScale();
    Mesh* m_Mesh;
    Vector2 m_Scale;
    float m_Radius;
	float m_Angle;//Direction angle stored in degrees
};

#endif