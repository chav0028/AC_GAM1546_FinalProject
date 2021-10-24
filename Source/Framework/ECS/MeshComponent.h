#pragma once
#include "Component.h"
#include <vector>

struct VertexFormat
{
	float m_Position[2];
	float m_UV[2];
	unsigned char m_Color[4];
};

class MeshComponent :
	public Component
{
public:
	MeshComponent(VertexFormat verticesAttributes[],unsigned int numberVertices, unsigned int numberIndices,unsigned int indices[],Entity* owner);
	~MeshComponent();

private:
	void setUniforms();

    GLuint m_VBO;
    GLuint m_IBO;

    VertexFormat m_VerticesAttributes;
    unsigned int m_Indices;

    void fillIBO();
    void fillVBO();

};