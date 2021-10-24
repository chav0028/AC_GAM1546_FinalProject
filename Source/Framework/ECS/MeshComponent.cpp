#include "CommonHeader.h"

MeshComponent::MeshComponent(VertexFormat verticesAttributes*, unsigned int numberVertices, unsigned int numberIndices, unsigned int indices*, Entity* aOwner) : Component(aOwner, "MeshComponent")
{

}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::setUniforms()
{
	//Get and save the shader program
	GLuint shaderProgram = GameFramework::getInstance()->getResourcesManager()->getActiveShaderProgram()->m_Program;
	glUseProgram(shaderProgram);//Set program to use

	//Set the object position uniform
	GLint objectPositionLoc = glGetUniformLocation(shaderProgram, "u_ObjectPosition");
	if(objectPositionLoc!=-1)//Check for valid location
	{
		glUniform2f(objectPositionLoc, m_OwnerEntity->getPosition().x, m_OwnerEntity->getPosition().y);//Set position according to its parent entity
	}
	
	//Set the object scale uniform
	GLint objectsScaleLoc = glGetUniformLocation(shaderProgram, "u_ObjectScale");
	if (objectPositionLoc != -1)//Check for valid location
	{
		glUniform2f(objectsScaleLoc, m_OwnerEntity->getScale().x, m_OwnerEntity->getScale().y);//Set scale according to its parent entity
	}

	//Set the camera position uniform, probably set in camera class or use active scene
	//GLint cameraPositionLoc = glGetUniformLocation(shaderProgram, "u_ObjectPosition");
	//if (cameraPositionLoc != -1)//Check for valid location
	//{
	//	glUniform2f(cameraPositionLoc, 0,0);
	//}

	//Set the projection scale uiform
	//GLint projectionScaleLoc = glGetUniformLocation(shaderProgram, "u_ProjectionScale");
	//if (objectPositionLoc != -1)//Check for valid location
	//{
	//	glUniform2f(projectionScaleLoc, 0,0);
	//}

	//Set the object color uniform
	//GLint objectColorLoc = glGetUniformLocation(shaderProgram, "u_ObjectColor");
	//if (objectPositionLoc != -1)//Check for valid location
	//{
	//	glUniform4f(objectColorLoc, m_objectColor.x,m_objectColor.y,m_objectColor.z.m_objectColor.w);
	//}


	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glActiveTexture(GL_TEXTURE0 + 0);
	//glBindTexture(GL_TEXTURE_2D, m_Texture);
	//Set  texture uniform
	//GLuint textureLoc = glGetUniformLocation(shaderProgram, "u_Texture");
	//if (textureLoc != -1)
	//{
	//	glUniform1i(textureLoc, 0);
	//}

	
	//Set  UV offset  uniform
	//GLuint uVOffsetLoc = glGetUniformLocation(shaderProgram, "u_UVOffset");
	//if (uVOffsetLoc != -1)
	//{
	//	glUniform2f(uVOffsetLoc, m_UVOffset.x, m_UVOffset.y);
	//}

	//Set animation time unifrom
	//GLuint animationTimeLoc = glGetUniformLocation(shaderProgram, "u_AnimationTime");
	//if (animationTimeLoc != -1)
	//{
	//	glUniform1f(animationTimeLoc, m_AnimationTime);
	//}

}