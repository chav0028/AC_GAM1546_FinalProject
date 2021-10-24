#ifndef __MESH__H__
#define __MESH__H__

#include <vector>
#include "GameObject.h"
#include "Framework/Services/Structs.h"

const unsigned int MAX_NUM_COLORS = 255;

class GameObject;

/*The structure or shape (with its properties) of something we can draw. .*/
class Mesh
{
public:
    Mesh(MeshFormat aMeshFormat, std::string aName);//Default values for indices in case we don't use IBO
    ~Mesh();

    void draw(GameObject* objectDrawn,Vector2 cameraPosition, Vector2 projectionScale);

    Vector2 getSize(){ return m_Size; }
    float getRadius();//Not 100% accurate radius

private:
    void fillIBO(unsigned int* indices);
    void fillVBO(VertexFormat* verticesAttributes);

    void setUniforms(GameObject* objectDrawn);
    void setAttributes(GameObject* objectDrawn);

    void drawVBO(GameObject* objectDrawn);
    void drawIBO(GameObject* objectDrawn);

    void useTexture(GLuint texture);

    GLuint m_VBO;
    GLuint m_IBO;

    Vector2 m_Size;//Since the size of an object is determined with hardcoded values, these ones are stored in the mesh class

    unsigned int m_NumberOfIndices;
    unsigned int m_NumberOfVertices;

    GLenum m_PrimitiveType;

    GLuint getAndUseShaderProgram(GameObject* objectDrawn);

	//This variables are passed through the call function. They are only member variables to have access through them from draw and setuniforms without parameters.
	Vector2 m_CameraPosition;
	Vector2 m_ProjectionScale;

    std::string m_MeshName;//Useful for debugging
};

#endif