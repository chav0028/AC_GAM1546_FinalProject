#ifndef __SCENEMANAGER__H__
#define __SCENEMANAGER__H__

#include <vector>

class Scene;

/*Class to potentially, ideally manage multiple scenes*/
class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void update(double delta);
    void draw();
    void loadContent();
    void onSurfaceChanged();

    void addScene(Scene* sceneAdded);
    void removeScene(Scene* sceneRemoved);

    Scene* getActiveScene();
    void setActiveScene(Scene* scene);

private:
    std::vector <Scene*> m_Scenes;
    Scene* m_ActiveScene;
};

#endif