#ifndef __CAMERA__H__
#define __CAMERA__H__

class GameObject;

const float CAMERA_SPEED_PCT_FROM_FOLLOWING_TARGET = 0.5f;//The speed percentage the camera speed will have in comparison to the target it is following
const Vector2 CAMERA_DEAD_ZONE_DEFAULT_SIZE = Vector2(5, 5);
const float CAMERA_DISTANCE_FROM_OBJECT_SMOOTHING = 1;
const float CAMERA_SMOOTHING_SPEED_REDUCTION = 0.1f;

/*A camera class, this class handles calling the game draw object methods (doesn't draw map background) and settign the correct viewport for that draw
the class also handles passing a "camera" position used to correctly place game objects*/
class Camera
{
public:
	Camera(Vector2 projectionScale);
	~Camera();

    void setViewportSettings(Vector2 position, Vector2 size);//We don't use vec2 as arguments for readability

    void draw();

    void addMultipleObjectsToDraw(std::vector<GameObject*>objectsToDraw);
	void addObjectToDraw(GameObject* objectToDraw);

	void followObject(GameObject* objectToFollow, double delta);//This functions would need to be call in an update
	bool checkTargetInDeadZone(Vector2 aTargetPosition);
	void boundsCollisionActiveScene();

    //Getters and setters (there are some to set individual values, but normally the vec2 are used)
    void setCameraPos(Vector2 aPosition){ m_Position = aPosition; }
    Vector2 getPosition(){ return m_Position; }

    void setCameraXPosX(float aX) { m_Position.x = aX; }
    float getCameraXPos(){ return m_Position.x; }

    void setCameraYPos(float aY) { m_Position.y = aY; }
    float getCameraYPos(){ return m_Position.y; }

    Vector2 getCameraPosition(){ return m_Position; }
    void setCameraPositon(Vector2 aCameraPosition){ m_Position = aCameraPosition; }

    void setCameraSize(Vector2 aSize){ m_CameraSize = aSize; }
    Vector2 getCameraSize(){ return m_CameraSize; }

    Vector2 getViewportPosition(){ return m_ViewportPosition; }

    void setCameraWidth(float W){ m_CameraSize.x = W; }
    float getCameraWidth(){ return m_CameraSize.x; }

    void setCameraHeight(float H) { m_CameraSize.y = H; }
    float getCameraHeight() { return m_CameraSize.y; }

	void setCameraDeadZoneSize(Vector2 aSize) { m_deadZoneSize = aSize; }

    Vector2 getProjectionScale(){ return m_ProjectionScale; }
    

protected:
    Vector2 m_ViewportPosition;
    Vector2 m_CameraSize;
    
	Vector2 m_Position;//Camera position
	float m_CameraSpeed;

	Vector2 m_deadZoneSize;//The area where a player can move, before we have to move the camera. Made to avoid needlessly moving the camera for every small movement

	Vector2 m_ProjectionScale;

    bool m_ViewportSet;//To avoid errors, make variable to ensure we don't call glViewport unless we have specified, the viewport settings
	std::vector <GameObject*> m_GameObjectsToDraw;//This are deleted in the 
};

#endif