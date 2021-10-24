/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : -Modified GameObject.cpp to now have a function to give the angle between the object's position and another position.

November 30 :-Added some more game logic implemented functions to GameObject as MoveGameObjectAngleSpeed, and boundsCollisionActiveScene.

December 1: =Added function to calculate angle between an 

*/

#include "CommonHeader.h"

GameObject::GameObject(ShaderProgramIndex aIndexShaderProgram, std::string aName) :
m_GameObjectName(aName),
m_AnimationTimer(0),
m_Mesh(nullptr),
m_IndexTextureToUse(0),
m_Color(Vector4Int(0,255,0,255)),
m_UVOffset(0,0),
m_UVScale(1,1),
m_Speed(0),
m_Radius(1),
m_Position(0), 
m_Scale(1),
m_AnimationTime(0),
m_BackColor(Vector4Int(0, 0, 0, 0)),//By default transparent since not all shapes would have it
m_IndexShaderProgramToUse(aIndexShaderProgram),
m_Angle(GAMEOBJECT_DEFAULT_ANGLE),
m_Enabled(true)
{    
}


GameObject::~GameObject()
{
    //The mesh will be deleted in the resources manager
}

void GameObject::update(double aDelta)
{
    //Empty so that it an overwritten
}

void GameObject::reset()
{
    //Empty so that it an overwritten
    m_Enabled = true;
}

void GameObject::draw(Vector2 aCameraPosition,Vector2 aProjectionScale)
{ 
     if (m_Enabled == true)
    {
        //If the object has a mesh
        if (m_Mesh != nullptr)
        {
            m_Mesh->draw(this, aCameraPosition, aProjectionScale);//Draw it
        }
    }
}

void GameObject::loadContent()
{
    //Empty so that it can be overwritten
}


//Sets the angle, it works only in degrees. It checks that the value passed is aa valid value
void GameObject::setAngle(float aAngle)
{
    //360 is the angle of a circle, and possible rotation angles of an object

    //Check if the angle is greater than 360
    if (aAngle > 360)
    {
        m_Angle=aAngle - 360;//If it is greater than 360, set the angle back to 0 (a spin in the circle)
    }
    else if (aAngle<0)//IF the angle is less than 0
    {
        m_Angle= aAngle+ 360;//If it is less than 0, set the angle to 360, as a circle spin
    }
    else
    {
        m_Angle = aAngle;//Set the angle normally
    }
}

//Returns the angle in degrees, it checks that the angle is in the degrees correct range
float GameObject::getAngle()
{
    //Check if the angle is greater than 360, in theory with the setter it should
	//never go through this check, but just as an extra check
    //if (m_Angle > 360)
    //{
    //    return 360;//If it is greater than 360, return 360
    //}
    //else if (m_Angle>0)//IF the angle is less than 0
    //{
    //    return 0;//If it is less than 0, return 0
    //}

        return m_Angle;//return the angle normally
}

//Moves a game object according to his speed and direction
void GameObject::MoveGameObjectAngleSpeed(double aDelta,bool aMoveForward)
{
	//Convert angle to radians
	float angleRad = m_Angle*PI / 180.0f;//Multiply angle in degrees by PI, and divide by 180

    float stepX = (cosf(angleRad))*(m_Speed*(float)aDelta);//Calculate the movement on X axis
    float stepY = (sinf(angleRad))*(m_Speed*(float)aDelta);//Calculate movement on Y axis

	if (aMoveForward == true)//If we are moving forward
    {
		m_Position = m_Position + Vector2(stepX, stepY);//Add the amount we moved to the current position
	}
	else//If we are moving backward, but without changing the angle
	{
		m_Position = m_Position - Vector2(stepX, stepY);//Add the amount we moved to the current position
	}
}

//Function that checks for collision between the current gameObject and another GameObject.It returns
//a bool, true if there was a collision, false if there was no collision.
bool GameObject::circleCollisionCheck(GameObject *aObject)
{
	if (aObject != nullptr)//Check that pointer isn't null
	{
		//the other objects position
		Vector2 objectPosition = aObject->getPosition();

		//if distance<=(radius1+radius2)^2 there is a collision
		float distance = calculateDistanceBetween(objectPosition);//Calculate distance using pythagorean theorem
		float sumRadius = m_Radius + aObject->getRadius();//Add radius of both objects

		if (distance < sumRadius)//check if they collide
		{
			return true;
		}
	}

	return false;//If they don't collide

}

//Calculates the distance between this object position and another position
float GameObject::calculateDistanceBetween(Vector2 aPosition)
{
    //calculate distance using Pythagorean Theorem 
    //distance=Sqrt(x^2+y^2)
    //distance=sqrt((x-x2)^2+(y-y2)^2)
    float distance = sqrtf(((m_Position.x - aPosition.x)*(m_Position.x - aPosition.x)) + ((m_Position.y - aPosition.y)*(m_Position.y - aPosition.y)));

    return distance;

}

//Check if the player is colliding with the map boundings of the active scene
bool GameObject::boundsCollisionActiveScene()
{
    Scene* activeScene = GameFramework::getInstance()->getSceneManager()->getActiveScene();//Get the currently active scene
    bool outOfBounds = false;
    if (activeScene != nullptr)	//If the scene is not null
    {
        //Save the size of the scene
        float sceneWidth = activeScene->getSceneHeight();
        float sceneHeight = activeScene->getSceneWidth();

        //Verticalbounds
        if (m_Position.x <= 0 + m_Radius)//Checks for the left side
        {
            m_Position.x = m_Radius;//Sets back his position
            outOfBounds = true;//set that it reached the bounds
        }
        else if (m_Position.x >= sceneWidth - m_Radius)//Check for right side
        {
            m_Position.x = sceneWidth - m_Radius;//Set back his position
            outOfBounds = true;//set that it reached the bounds
        }

        //Horizontal bounds
        if (m_Position.y <= 0 + m_Radius)//Check bottom side
        {
            m_Position.y = 0 + m_Radius;//Set back his position
            outOfBounds = true;//set that it reached the bounds
        }
        else if (m_Position.y >= sceneHeight - m_Radius)//Check top side
        {
            m_Position.y = sceneHeight - m_Radius;//Set back his position
            outOfBounds= true;//set that it reached the bounds
        }
    }

    //Don't Return the value until it has gone (and be moved) by all the checks
    return outOfBounds;
}

float GameObject::getAngleBetween(Vector2 aPosition)
{
    //Use the arctangent between the position vectors to get the angle
    float adjacent = m_Position.x - aPosition.x;//Get the adjacent
    float opposite = m_Position.y - aPosition.y; //Get the opposite

    float angle = atan2f(opposite, adjacent);//Calculate the angle between them
    angle = angle*180.0f / PI;//Convert the angle from radians to degrees

    return angle;//return the angle back in degrees
}

void GameObject::setScale(Vector2 aScale)
{
    //Account that the radius will change once the scale changes
    m_Scale = aScale;

    //Update radius
    setRadiusMeshScale();
}

float GameObject::getRadius()
{    
    return m_Radius;
}

void GameObject::setMesh(Mesh* aMesh)
{
    if (aMesh != nullptr)
    {
        m_Mesh = aMesh;

        //Update the radius
        setRadiusMeshScale();
    }
}

//Set radius according to the mesh and scale
void GameObject::setRadiusMeshScale()
{
    if (m_Mesh != nullptr)
    {
        m_Radius = m_Mesh->getRadius()*((m_Scale.x + m_Scale.y) / 2);//Account for scale (/2 to get average in x and y)
    }   
    else
    {
        m_Radius = 0;
    }  
}