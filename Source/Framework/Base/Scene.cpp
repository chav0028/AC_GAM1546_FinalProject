/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : Mamage all objects in the scene.

November 29 :
-Modified all the draw methods to take as parameter the camera position and projection scale.
-Modified scene to store a vector of camera, and instead of drawing all the gameobjects, now it will draw all the cameras.
-Mesh class now is correctly setting all the uniforms by obtaining from the draw method (cameraposition and projection scale) and from the parent object members.
-Modified vertex shader to take into account the object rotation.
*/


#include "CommonHeader.h"

using namespace std;

Scene::Scene(string aID) : m_SceneID(aID)  ,
m_OffscreenBackgroundColor(DEFAULT_SCENE_OFFSCREEN_COLOR),
m_SceneSize(Vector2(0.0f,0.0f)),
m_BackgroundRectangle(nullptr)
{
    //Set name of scene in initialisers list
}


Scene::~Scene()
{
    //Delete all the game objects in the scene
    while (m_SceneGameObjects.empty() == false)
    {
        //Delete the game object
        if (m_SceneGameObjects.back() != nullptr)
        {
            delete m_SceneGameObjects.back();
            m_SceneGameObjects.back() = nullptr;
        }

        //Remove object from vector
        m_SceneGameObjects.pop_back();
    }

    //Delete cameras
    while (m_SceneCameras.empty() == false)
    {
        //Delete the camera
        if (m_SceneCameras.back() != nullptr)
        {
            delete m_SceneCameras.back();
            m_SceneCameras.back() = nullptr;
        }

        //Remove object from vector
        m_SceneCameras.pop_back();
    }

    //Delete background
    if (m_BackgroundRectangle != nullptr)
    {
        delete m_BackgroundRectangle;
        m_BackgroundRectangle = nullptr;
    }

}

void Scene::update(double aDelta)
{
    //Update all the game objects
    for (unsigned int i = 0; i < m_SceneGameObjects.size(); i++)
    {
        if (m_SceneGameObjects.at(i)!=nullptr)
        {
            m_SceneGameObjects.at(i)->update(aDelta);
        }
    } 
}

void Scene::onSurfaceChanged()
{
//Empty so that it can be overwritten
}

void Scene::draw()
{
    // clear the screen to game offscreen settings
    glClearColor(m_OffscreenBackgroundColor.x, m_OffscreenBackgroundColor.y, m_OffscreenBackgroundColor.z, m_OffscreenBackgroundColor.w);//clear screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw all the cameras in the scene
	if (m_SceneCameras.empty() == false)//if we have cameras
	{
        
		//Go through all the cameras
		for (unsigned int i = 0; i < m_SceneCameras.size(); i++)
		{
            if (m_SceneCameras.at(i)!= nullptr)
            {
                if (i == 0)//Always supposing the first camera is the main game camera
                {
                    m_BackgroundRectangle->draw(m_SceneCameras.at(i)->getCameraPosition(), m_SceneCameras.at(i)->getProjectionScale());//Draw background
                }

                m_SceneCameras.at(i)->draw();//Draw each camera

                CheckForGLErrors();
            }
		}
	}

}

void Scene::loadContent()
{
    //Load all the objects
    for (unsigned int i = 0; i < m_SceneGameObjects.size(); i++)
    {
        if (m_SceneGameObjects.at(i) != nullptr)
        {
            m_SceneGameObjects.at(i)->loadContent();
        }
    }

    reset();//Setup the scene
}

void Scene::reset()
{
    //Reset all the objects
    for (unsigned int i = 0; i < m_SceneGameObjects.size(); i++)
    {
        if (m_SceneGameObjects.at(i) != nullptr)
        {
            m_SceneGameObjects.at(i)->reset();
        }
    }
}

void Scene::addGameObject(GameObject* aGameObject)
{
    if (aGameObject != nullptr)//Check that we are adding a valid object
    {
        m_SceneGameObjects.push_back(aGameObject);//Add the game object to the vector
    }
}

void Scene::addMultipleGameObjects(vector<GameObject*> aGameObjects)
{
    //Go through all the game objects
    for (unsigned int i = 0; i < aGameObjects.size(); i++)
    {
        addGameObject(aGameObjects.at(i));//Add them to the scene, add game objects will check that they are valid
    }
}

GameObject* Scene::getGameObjectAtIndex(unsigned int aIndex)
{
    if (aIndex < m_SceneGameObjects.size())//if it is a valid index
    {
        if (m_SceneGameObjects.at(aIndex) != nullptr)
        {
            return m_SceneGameObjects.at(aIndex);
        }
    }

    return nullptr;
}

void Scene::removeGameObject(GameObject* aGameObject)
{
    if (aGameObject != nullptr)
    {
        //Can't use pop_back to remove the object since it may not be at the end of the vector.
        //So  erase needs to be used in order to remove it from vector, and since it is a pointer it also
        // has to manually delete it.
        int index = getIndexForGameobject(aGameObject);//Get the index of the object
        if (index != -1)//if the object was found in the vector of objects
        {
            //Delete the object (check for nullptr already done at the start of the function)
            delete aGameObject;
            aGameObject = nullptr;

            //Remove object from memory
            m_SceneGameObjects.erase(m_SceneGameObjects.begin() + index);//Remove the object from the vector
        }
    }
}

int Scene::getIndexForGameobject(GameObject* aGameObject)
{
    //Check that there is a valid object
    if (aGameObject != nullptr)
    {
        //Look for the object in the scene
        for (unsigned int index = 0; index < m_SceneGameObjects.size(); index++)
        {
            //If the object is find
            if (m_SceneGameObjects.at(index) == aGameObject)
            {
                return index;//Return the position at it was find
            }
        }
    }

    return -1;//If it wasn't find , return -1 to indicate an error
}

void Scene::addCamera(Camera* aCamera)
{
	if (aCamera != nullptr)//Check that we are adding a valid camera
	{
		m_SceneCameras.push_back(aCamera);//Add the camera to the vector
	}
}

int Scene::getCameraIndex(Camera* aCamera)
{
	//Check that there is a valid camera
	if (aCamera != nullptr)
	{
		//Look for the object in the scene
		for (unsigned int index = 0; index < m_SceneCameras.size(); index++)
		{
			//If the object is find
			if (m_SceneCameras.at(index) == aCamera)
			{
				return index;//Return the position at it was find
			}
		}
	}

	return -1;//If it wasn't find , return -1 to indicate an error
}

Camera* Scene::getCameraAtIndex(unsigned int  aIndex)
{
    if (aIndex < m_SceneCameras.size())//Check it is a valid index
    {
        return m_SceneCameras.at(aIndex);
    }

    return nullptr;
}

void Scene::RemoveCamera(Camera* aCamera)
{
	if (aCamera != nullptr)
	{
		int index = getCameraIndex(aCamera);//Get the index of the object
		if (index != -1)//if the object was found in the vector of objects
		{
			//Delete the object (check for nullptr already done at the start of the function)
			delete aCamera;
			aCamera = nullptr;

			//Remove object from memory
			m_SceneCameras.erase(m_SceneCameras.begin() + index);//Remove the object from the vector
		}
	}

}
