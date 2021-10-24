/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : se24 and get key presses

November 22 :
--Made the g_keystates a member variable of the input manager.
*/

#include "CommonHeader.h"

SceneManager::SceneManager():
m_ActiveScene(nullptr)
{
}

SceneManager::~SceneManager()
{
    //While there are still scenes
    while (m_Scenes.empty() == false)
    {
        if (m_Scenes.back() != nullptr)
        {

            //If it was the active scene set it to null
            if (m_Scenes.back() == m_ActiveScene)
            {
                m_ActiveScene = nullptr;
            }

            //Delete the last scene in the vector
            delete m_Scenes.back();
            m_Scenes.back() = nullptr;

        }
        m_Scenes.pop_back();//Remove the element from the vector
    }

    //Normally this wouldn't be call, since when we set the active scene we would add it to the scene vector.
    //But if somehow the active scene is not in the scenes manager vector, delete it
    if (m_ActiveScene != nullptr)
    {
        delete m_ActiveScene;
        m_ActiveScene = nullptr;
    }
}

//Gets called when window is resized, unlike the framework, this doesn't take any parameter. Since the size of the window is handled by the Framework
void SceneManager::onSurfaceChanged()
{
    //Tell all the scenes the window was resized
    for (unsigned int i = 0; i < m_Scenes.size(); i++)
    {
        if (m_Scenes.at(i) != nullptr)
        {
            m_Scenes.at(i)->onSurfaceChanged();//Notify them the window sie changed
        }
    }
}

void SceneManager::update(double aDelta)
{
    //If we have an active scene
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->update(aDelta);//Update the active scene
    }
}

void SceneManager::draw()
{
    //If we have an active scene
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->draw();//Draw the active scene
    }

    CheckForGLErrors();
}

void SceneManager::loadContent()
{
    //Go through all the scenes
    for (unsigned int i = 0; i < m_Scenes.size(); i++)
    {
        if (m_Scenes.at(i) != nullptr)
        {
            m_Scenes.at(i)->loadContent();//Load the content in each scene
        }
    }

}

void SceneManager::addScene(Scene* aSceneAdded)
{

    if (aSceneAdded != nullptr)//Check that we are adding a valid scene
    {

        if (m_Scenes.empty() == true)//If we don't have any scene in the vector
        {
            m_ActiveScene = aSceneAdded;//Make this new scene our active one
        }

        m_Scenes.push_back(aSceneAdded);//Add the scene to the vector

    }

}


void SceneManager::removeScene(Scene* aSceneRemoved)
{
    if (aSceneRemoved != nullptr)//Check we are trying to remove a valid scene
    {
        for (unsigned int i = 0; i < m_Scenes.size(); i++)//Go through all the scenes
        {

            if (aSceneRemoved == m_Scenes.at(i))//If we find the scene to remove
            {
                //Delete the scene
                //if (m_scenes.at(i))//Unnecessary check since we already checked that aSceneRemoved is not null
                delete m_Scenes.at(i);
                m_Scenes.at(i) = nullptr;

                //Remove scene from vector
                m_Scenes.erase(m_Scenes.begin() + i);//Erase element at desired index.
            }
        }
    }

    //Now that removed the scene, check if we didn't delete the active scene
    if (m_ActiveScene == nullptr)//If the active scene is deleted
    {
        if (m_Scenes.size() > 0)//If we have more scenes in the vector
        {
            for (unsigned int i = 0; i < m_Scenes.size(); i++)//Look for the first valid scene in the vector
            {
                if (m_Scenes.at(i) != nullptr)//If the scene is valid
                {
                    //Make it the active scene
                    m_ActiveScene = m_Scenes.at(i);
                    break;//Break out from the loop, since we already found a new active scene
                }
            }
        }
    }
}


Scene* SceneManager::getActiveScene()
{
    if (m_ActiveScene != nullptr)//If the active scene is not null
    {
        return m_ActiveScene;//Return the active scene
    }

    //If the active scene is null, return null
    return nullptr;
}

void SceneManager::setActiveScene(Scene* aScene)
{
    if (aScene != nullptr)//Check if the scene we want to set active is valid
    {
        m_ActiveScene = aScene;//Set the active scene


        //Add the active scene to the vector, if it wasn't already in it.
        //don't check for null in active scene, since we already checked for the argument aScene
        if (m_Scenes.empty() == false)//Check if we have more scenes
        {
            for (unsigned int i = 0; i < m_Scenes.size(); i++)//Go through all scenes in the scene manager
            {
                if (m_ActiveScene == m_Scenes.at(i))//If we find the scene in the 
                {
                    break;//Break out of the loop
                }

                if (i == m_Scenes.size() - 1)//If we didn't find the active scene in the vector (m_scenes.size -1 , since we start the loop index at 0)
                {
                    addScene(m_ActiveScene);//Add it to the scenes vector
                }
            }
        }
        else//iF the vector of scenes is empty
        {
            addScene(m_ActiveScene);//Add it to the scenes vector
        }
    }
}