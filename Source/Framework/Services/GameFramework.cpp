/*
Student:    Alvaro Chavez Mixco
Date:       Tuesday, December 8 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Run the main game logic. Create game objects, update them, draw them and delete them.
Modification history:

*/

#include "CommonHeader.h"
#include <time.h>

/*Polish
___________________________________________________________________________________________________________________________________________________

-There is a safezone where the player and target spawn, so that the enemies don't spwan too close to that location
-The user can press R to restart the level, in case it ends up being unbeatable
-After the first level enemies get a random color, checking that is different from the map, player and target colors. The first level enemies start with a default color.
-When the user changes level, a different enemy shape gets drawn.
-There is an effect during transition similar to a fade out.
-Different transition images after completing each level, after the third level the sides of this images represent the current level.
-Screen cleared to different colors when there is a game and during transitions.

*/

//We need to create and set the pointer at the start of the code, to avoid a linker error.
GameFramework* GameFramework::s_InstanceFramework = nullptr;

GameFramework::GameFramework() :
m_WindowHeight(-1),
m_WindowWidth(-1),
m_Running(true),
m_WindowActive(true)
{
    //Create the managers
    m_SceneManager = new SceneManager;
    m_InputManager = new InputManager;
    m_ResourcesManagaer = new ResourcesManager;

    //Generate random number seed
    srand((unsigned int)time(0));//Use time for random, so that it is more random

}

GameFramework::~GameFramework()
{
    //Delte the services
    if (m_InputManager != nullptr)
    {
        delete m_InputManager;
        m_InputManager = nullptr;
    }

    if (m_SceneManager != nullptr)
    {
        delete m_SceneManager;
        m_SceneManager = nullptr;
    }

    if (m_ResourcesManagaer != nullptr)
    {
        delete m_ResourcesManagaer;
        m_ResourcesManagaer = nullptr;
    }
}

void GameFramework::update(double aDelta)
{
    //Check if the user wants to quit the program
    if (m_InputManager != nullptr)
    {
        //If the user pressed thE escape key
        if (m_InputManager->getKeyState(VK_ESCAPE) == true)
        {
            m_Running = false;//Stop the program
        }
    }

    //Update scene manager
    if (m_SceneManager != nullptr && m_Running == true)
    {
        m_SceneManager->update(aDelta);
    }

}

void GameFramework::draw()
{

    //Draw to the window
    if (m_SceneManager != nullptr)
    {
        m_SceneManager->draw(); //Draw the scenes in scene manager
    }

    CheckForGLErrors();
}

GameFramework* GameFramework::getInstance()
{
    //If  we don't have an instance
    if (s_InstanceFramework == nullptr)
    {
        s_InstanceFramework = new GameFramework();//Create one
    }

    //Return the instance
    return s_InstanceFramework;
}

void GameFramework::onSurfaceChanged(unsigned int aWidth, unsigned int aHeight)
{
    //Save the width and heigh of the window
    m_WindowWidth = aWidth;
    m_WindowHeight = aHeight;
	
	//If we have a scene manager
	if (m_SceneManager != nullptr)
	{
		m_SceneManager->onSurfaceChanged();//Notify the manager the scene changed
	}
}

void GameFramework::loadContent()
{
    // turn on depth buffer testing.
    //glEnable( GL_DEPTH_TEST );
    //glDepthFunc( GL_LESS );

    // turn on alpha blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Generate random number seed
    srand((unsigned int)time(0));//Use time for random, so that it is more random

    //iF there is a resources manager
    if (m_ResourcesManagaer != nullptr)
    {
        //Load resources manager, this must be done before loading the scnes
        m_ResourcesManagaer->loadContent();
    }

    //Load the scenes
    if (m_SceneManager != nullptr)
    {
        //Create the game scene
        m_SceneManager->addScene(new Game());

        m_SceneManager->loadContent();
    }


    CheckForGLErrors();
}

int GameFramework::getRandomNumberInRange(int aMinimumValue, int aMaxValue)
{
    int randomNumber = aMinimumValue + (rand() % (int)(aMaxValue - aMinimumValue + 1));//Get a random number (inclusive) between the values passed

    return randomNumber;
}