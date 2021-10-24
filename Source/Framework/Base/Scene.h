#ifndef __SCENE__H__
#define __SCENE__H__

#include <string>
#include <vector>

class GameObject;
class Camera; 
class Rectangle;

const Vector4 DEFAULT_SCENE_OFFSCREEN_COLOR = Vector4(0.2f, 0.5f, 1.0f, 1.0f);

/*A basic class to better manage the game objects..*/
class Scene
{
public:
    Scene(std::string iD);
    ~Scene();

    //Virtual basic scene methods
    virtual void update(double delta);
    virtual void draw();
    virtual void loadContent();
    virtual void reset();
    virtual void onSurfaceChanged();

    //Manage game objects methods
    void addGameObject(GameObject* gameObject);
    void addMultipleGameObjects(std::vector<GameObject*> gameObjects);
    void removeGameObject(GameObject* gameObject);

    int getIndexForGameobject(GameObject* gameObject);//Returns int instead of unsigned int, so that we can use -1 for error checking
    GameObject* getGameObjectAtIndex(unsigned int index);
	std::vector <GameObject*> getAllGameObjects() { return m_SceneGameObjects; }

	void addCamera(Camera* camera);
	void RemoveCamera(Camera* camera);
    unsigned int getNumberOfCameras(){ return m_SceneCameras.size(); }

    int getCameraIndex(Camera* camera);
    Camera* getCameraAtIndex(unsigned int index);

	Vector2 getSceneSize() { return m_SceneSize; }
	void setSceneSize(Vector2 aSize) { m_SceneSize = aSize; }

	float getSceneWidth() { return m_SceneSize.x; }
	void setSceneWidth(float aWidth) { m_SceneSize.x = aWidth; }

	float getSceneHeight() { return m_SceneSize.y; }
	void setSceneHeight(float aHeight) { m_SceneSize.y = aHeight; }

protected:
    RectangleObject* m_BackgroundRectangle;

private:
    std::vector <GameObject*> m_SceneGameObjects;
	std::vector<Camera*> m_SceneCameras; 

	Vector4 m_OffscreenBackgroundColor;
	Vector2 m_SceneSize;//Used in case we want to know the bounding box of a scene

	std::string m_SceneID;

};

#endif