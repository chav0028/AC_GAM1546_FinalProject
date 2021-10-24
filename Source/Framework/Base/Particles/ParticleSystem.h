#ifndef __PARTICLESYSTEM__H__
#define __PARTICLESYSTEM__H__

class ParticleRenderer;
class ParticleEmitter;
class ShaderProgram;

//Basic class to tie together a particle emitter with a particle renderer
class ParticleSystem
{
public:
	ParticleSystem(ShaderProgramIndex indexShaderProgram,GLuint texture=0);
	ParticleSystem(unsigned int maxParticles,ShaderProgramIndex indexShaderProgram, GLuint texture=0);
	~ParticleSystem();

	void setIndexShaderProgramToUse(ShaderProgramIndex aIndex) { m_IndexShaderProgramToUse = aIndex; }
	ShaderProgramIndex getIndexShaderProgramToUse() { return m_IndexShaderProgramToUse; }

	//Convenience method to get the shader program according to the system index
	ShaderProgram* getShaderProgramFromIndex();

	void createAddParticleEmitter(unsigned int maxNumberParticles);
	void addParticleEmitter(ParticleEmitter* emitter);

	ParticleEmitter* getParticleEmitter(unsigned int aIndex);
	ParticleRenderer* getParticleRenderer() { return m_ParticleRenderer; }

	virtual void update(double delta);
    virtual void draw(Vector2 cameraPosition, Vector2 projectionScale);

private:
	unsigned int m_MaxParticles;

	ParticleRenderer* m_ParticleRenderer;
	std::vector<ParticleEmitter*> m_ParticleEmitters;

	ShaderProgramIndex m_IndexShaderProgramToUse;
};

#endif