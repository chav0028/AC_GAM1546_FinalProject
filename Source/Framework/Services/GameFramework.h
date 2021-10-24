#ifndef __GAMEFRAMEWORK_H
#define __GAMEFRAMEWORK_H

#include <string>
#include <vector>

class InputManager;
class SceneManager;
class ResourcesManager;

/*Classs to intend to remove  globals by using the singleton pattern.*/
class GameFramework
{
public:
    ~GameFramework();
    void update(double delta);
    void draw();
    void loadContent();

    void onSurfaceChanged(unsigned int width, unsigned int height);

    InputManager* getInputManager(){ return m_InputManager; }
    SceneManager* getSceneManager(){ return m_SceneManager; }
    ResourcesManager* getResourcesManager(){ return m_ResourcesManagaer; }

    int getWindowHeight(){ return m_WindowHeight; }
    int getWindowWidth(){ return m_WindowWidth; }
    Vector2 getWindowSize(){ return Vector2((int)m_WindowWidth, (int)m_WindowHeight); }
    void setWindowWidth(GLsizei width){ m_WindowWidth = width; }
    void setWindowHeight(GLsizei height){ m_WindowHeight = height; }
    void setWindowSize(Vector2 size){ m_WindowWidth = (int)size.x; m_WindowHeight = (int)size.y; }

    //Singleton, returns the instance, and if we don't have one already create it
    static GameFramework* getInstance();

    void setRunning(bool status){ m_Running = status; }
    bool getRunning(){ return m_Running; }

    void setWindowActive(bool status){ m_WindowActive = status; }
    bool getWindowActive(){ return m_WindowActive; }

    int getRandomNumberInRange(int minimumValue, int maxValue);

private:
    std::vector <ShaderProgram*> m_Shaders;

    unsigned int m_WindowWidth;
    unsigned int m_WindowHeight;

    bool  m_WindowActive;
	bool m_Running;

    SceneManager* m_SceneManager;
    InputManager* m_InputManager;
    ResourcesManager* m_ResourcesManagaer;

    //Singleton, 1 instance, private constructor
    static GameFramework* s_InstanceFramework;
    GameFramework();

};

#endif