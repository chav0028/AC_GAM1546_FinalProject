#ifndef __PARTICLERENDERER__H__
#define __PARTICLERENDERER__H__

#include <string>
#include "Framework/Services/Structs.h"

class ShaderProgram;
class ParticleSystem;

/*the classs uses Dynamic Vertex  generation to draw the particles.*/
class ParticleRenderer
{
public:
	ParticleRenderer(ParticleSystem* ownerParticleSystem,GLuint texture=0);
	~ParticleRenderer();

	void addParticle(Particle particle);
    void draw(Vector2 cameraPosition, Vector2 projectionScale);

    void setNumberOfParticles(unsigned int aNumber){ m_NumberOfParticles = aNumber; }
	void setUpRenderer();

    void setTexture(GLuint texture);

private:
	VertexFormat* m_blockOfMemory;
	GLuint m_VBO;
	GLuint m_IBO;

	void fillVBO();
	void fillIBO();

    void setUniforms(Vector2 cameraPosition, Vector2 projectionScale);
    void setAttributes();

	unsigned int m_NumberOfIndices;
	unsigned int m_NumberOfParticles;

	ShaderProgram* m_Shader;
	ParticleSystem* m_OwnerParticleSystem;

	GLuint m_Texture;

};

#endif
