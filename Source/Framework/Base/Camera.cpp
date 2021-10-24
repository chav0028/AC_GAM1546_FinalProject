/*
Student:    Alvaro Chavez Mixco
Date:       Monday, October 19 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Set the viewport for the camera, and draw all the game objects in the game.


December 1: =Added function to follow an object

*/

#include "CommonHeader.h"

Camera::Camera(Vector2 aProjectionScale) :
	m_ProjectionScale(aProjectionScale),
	m_CameraSpeed(0),
	m_Position(0,0),
	m_deadZoneSize(CAMERA_DEAD_ZONE_DEFAULT_SIZE),
	m_ViewportSet(false)//To avoid errors, make variable to ensure we don't call glViewport unless we have specified,
	//the viewport settings
	{
	}

	Camera::~Camera()
{
	//Empty, this class doesn't handle deleting the objects. Ideally that would be done in the scene class
}

void Camera::setViewportSettings(Vector2 aPosition, Vector2 aSize)//We don't use vec2 as arguments for readability
{
	m_ViewportPosition = aPosition;//Assign the values
	m_CameraSize = aSize;
	m_ViewportSet = true;
}

void Camera::draw()
{
	//HAVE TO SET THE VIEWPORT SETTINGS BEFORE DRAWING THE CAMERA
	if (m_ViewportSet == true)
	{
		glViewport((GLint)m_ViewportPosition.x, (GLint)m_ViewportPosition.y, (GLsizei)m_CameraSize.x, (GLsizei)m_CameraSize.y);//Set the viewport
	}

	//Draw the game objects
	if (m_GameObjectsToDraw.empty() == false)//If we have game objects to draw
	{
		for (unsigned int i = 0; i < m_GameObjectsToDraw.size(); i++)//Go through all of them
		{
			m_GameObjectsToDraw.at(i)->draw(m_Position, m_ProjectionScale);//Draw according to the camera position
		}
	}
}

void Camera::addMultipleObjectsToDraw(std::vector<GameObject*> objectsToDraw)
{
	if (objectsToDraw.empty() == false)//Check that the vector is not empty
	{
		for (unsigned int i = 0; i < objectsToDraw.size(); i++)//Add all the objects to the draw vector
		{
			if (objectsToDraw.at(i) != nullptr)//If it is a valid object
			{
				m_GameObjectsToDraw.push_back(objectsToDraw.at(i));//Add it to draw vector
			}
		}
	}
}

void Camera::addObjectToDraw(GameObject * aObjectToDraw)
{
	if (aObjectToDraw != nullptr)//If it is a valid object
	{
		m_GameObjectsToDraw.push_back(aObjectToDraw);//Add it to draw vector
	}
}

void Camera::followObject(GameObject * aObjectToFollow, double aDelta)
{

	if (checkTargetInDeadZone(aObjectToFollow->getPosition()) == false)//If the target is not in the dead zone, follow him
	{
		float distanceFromTarget = aObjectToFollow->calculateDistanceBetween(m_Position);//Get how far the camera is from the target
		m_CameraSpeed = aObjectToFollow->getSpeed()*CAMERA_SPEED_PCT_FROM_FOLLOWING_TARGET;//Get the camera speed according to the speed of the object
		float angleFromTarget = aObjectToFollow->getAngleBetween(m_Position);//Get the angle between the camera and the target
		angleFromTarget = angleFromTarget*PI / 180;//Convert the angle to radians
		float finalSpeed = 0;//Temporary variable to hold the speed, according to the calculations from camera speed and framerate, etc.

		if (distanceFromTarget > CAMERA_DISTANCE_FROM_OBJECT_SMOOTHING)
		{
			finalSpeed = (m_CameraSpeed*(float)aDelta)*(distanceFromTarget*CAMERA_SMOOTHING_SPEED_REDUCTION);//Get the speed according to the target, and reduce it as the camera gets close to target

			float stepX = cosf(angleFromTarget)*finalSpeed;//Calculate the movement on X axis
			float stepY = sinf(angleFromTarget)*finalSpeed;//Calculate movement on Y axis

			m_Position += Vector2(stepX, stepY);//Move  the camera toward the target
		}
		else//Move the camera normally
		{
			finalSpeed = m_CameraSpeed*(float)aDelta;//Get speed according to frame rate

			float stepX = cosf(angleFromTarget)*finalSpeed;//Calculate the movement on X axis
			float stepY = sinf(angleFromTarget)*finalSpeed;//Calculate movement on Y axis

			m_Position += Vector2(stepX, stepY);//Move  the camera toward the target
		}
	}
}

//Check if the target has moved from his designed "dead zone"
bool Camera::checkTargetInDeadZone(Vector2 aTargetPosition)
{
	//Divide the size of the deadzone by 2, so that we can center it
	float halfWidth = m_deadZoneSize.x / 2;
	float halfHeight = m_deadZoneSize.y / 2;

	//Horizontal bounds
    if ((aTargetPosition.x >= m_Position.x - halfWidth &&//Check left side
        aTargetPosition.x <= m_Position.x + halfWidth)&&//Check right side
        (aTargetPosition.y >= m_Position.y - halfHeight &&//Check bottom side
        aTargetPosition.y <= m_Position.y + halfHeight)//Check top side
        )
    {
        return true;//Return that the player is in the deadzone
    }

	return false;//Return that the target is not the deadzone
}
