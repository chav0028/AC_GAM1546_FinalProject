/*
Student:    Alvaro Chavez Mixco
Date:       Monday, October 19 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Draw all the particles of a single type, this is done
uisng dynamic vertices


December 1: =Adapted code from class to file
December 6: n ParticleRenderer.cpp, made function setUpRenderer to fill IBO and create a block of memory. Made into a function in 
case the total number of particle changes in the Particle sys
*/

#include "CommonHeader.h"

ParticleRenderer::ParticleRenderer(ParticleSystem* aOwnerParticleSystem, GLuint aTexture) :
m_OwnerParticleSystem(aOwnerParticleSystem),
m_NumberOfParticles(0),
m_NumberOfIndices(0),
m_blockOfMemory(nullptr),
m_Texture(aTexture)
{
    //Generate VBO
    glGenBuffers(1, &m_VBO);

    //Save the shader program
    if (aOwnerParticleSystem != nullptr)
    {
        m_Shader = m_OwnerParticleSystem->getShaderProgramFromIndex();
        //m_Shader = GameFramework::getInstance()->getResourcesManager()->getShaderProgram();
    }

    setUpRenderer();//Creates the block of memory and fill the ibo
}

ParticleRenderer::~ParticleRenderer()
{
    if (m_blockOfMemory != nullptr)
    {
        delete[] m_blockOfMemory;
        m_blockOfMemory = nullptr;
    }

    //Delete the buffers
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);

}

void ParticleRenderer::draw(Vector2 aCameraPosition, Vector2 aProjectionScale)
{
    if (m_NumberOfIndices == 0 || m_NumberOfParticles == 0)
    {
        return;
    }

    GLuint shader = m_Shader->m_Program;
    glUseProgram(shader);

  
    fillVBO();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    setAttributes();
    setUniforms(aCameraPosition, aProjectionScale);

    CheckForGLErrors();

    glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, (void*)0);

    CheckForGLErrors();
}

//Creates the block of memory, and fills the IBO
void ParticleRenderer::setUpRenderer()
{
    //Create a block of memory
    m_blockOfMemory = new VertexFormat[PARTICLES_RENDERER_MAX_NUMBER_OF_PARTICLES * 4];//create an array with the maximum number of particles *4 because it will have 4 indices

    //Fill the IBO
    fillIBO();
}

void ParticleRenderer::fillVBO()
{
    // fill buffer with our attributes
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * (m_NumberOfParticles * 4), m_blockOfMemory, GL_DYNAMIC_DRAW);

    // check for errors
    CheckForGLErrors();
}

void ParticleRenderer::fillIBO()
{
    //Generate IBO
    glGenBuffers(1, &m_IBO);

    unsigned int maxNumParticles = PARTICLES_RENDERER_MAX_NUMBER_OF_PARTICLES;

    if (maxNumParticles > 0)//If there are actually particles to render
    {
        unsigned int* indices;
        indices = new unsigned int[maxNumParticles * 6];//* 6 because it uses 6 indices

        //Fill the indices array
        for (unsigned int i = 0; i < maxNumParticles; i++)
        {
            //I*6 is the number of the particle currently being modified, since each particle has 6 indices
            indices[(i * 6) + 0] = i * 4 + 0;//i*4 represents the vertices, since the particle has 4 vertice.
            indices[(i * 6) + 1] = i * 4 + 1;
            indices[(i * 6) + 2] = i * 4 + 2;
            indices[(i * 6) + 3] = i * 4 + 0;
            indices[(i * 6) + 4] = i * 4 + 2;
            indices[(i * 6) + 5] = i * 4 + 3;
        }

        //Generate the IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);//Use elemnt array buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * (maxNumParticles * 6), indices, GL_STATIC_DRAW);

        delete[] indices;
    }
}

void ParticleRenderer::setUniforms(Vector2 aCameraPosition, Vector2 aProjectionScale)
{
    //Set shader to use
    GLuint shader = m_Shader->m_Program;

    //Set the object scale uniform
    GLint objectsScaleLoc = glGetUniformLocation(shader, "u_ObjectScale");
    if (objectsScaleLoc != -1)//Check for valid location
    {
        glUniform2f(objectsScaleLoc, PARTICLES_DEFAULT_SCALE.x, PARTICLES_DEFAULT_SCALE.y);//Set scale according to its parent object
    }

    //Set the camera position uniform  
    Vector2 inverseCameraPos = aCameraPosition*-1;//Multiply by -1 to get inverse position
    GLint cameraPositionLoc = glGetUniformLocation(shader, "u_CameraPosition");
    if (cameraPositionLoc != -1)//Check for valid location
    {
        glUniform2f(cameraPositionLoc, inverseCameraPos.x, inverseCameraPos.y);//Camera position is passed in the draw function
    }

    //Set the projection scale uiform
    GLint projectionScaleLoc = glGetUniformLocation(shader, "u_ProjectionScale");
    if (projectionScaleLoc != -1)//Check for valid location
    {
        glUniform2f(projectionScaleLoc, aProjectionScale.x, aProjectionScale.y);//Projection scale is passed in the draw function
    }

    //If we have a texture
     if (m_Texture > 0)
    {
        //Bind and activate the the texture
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        //Activate and bind the texture
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, m_Texture);

        //Set  texture uniform
        GLuint textureLoc = glGetUniformLocation(shader, "u_Texture");
        if (textureLoc != -1)
        {
            glUniform1i(textureLoc, 0);//Binds the texture to image unit 0.
        }

        //Set  UV offset  uniform
        GLuint uVOffscaleLoc = glGetUniformLocation(shader, "u_UVScale");
        if (uVOffscaleLoc != -1)
        {
            glUniform2f(uVOffscaleLoc, PARTICLES_DEFAULT_UV_SCALE.x, PARTICLES_DEFAULT_UV_SCALE.y);//The offset is obtained from a set function
        }

    }
}

void ParticleRenderer::setAttributes()
{
    //Set shader to use
    GLuint shader = m_Shader->m_Program;

    //Set attributes
    GLsizei stride = sizeof(VertexFormat);//Save the size of the vertex format

    //Positon
    GLint posloc = glGetAttribLocation(shader, "a_Position");
    if (posloc != -1)
    {
        glVertexAttribPointer(posloc, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(posloc);
    }

    //UV Coords
    GLint uvloc = glGetAttribLocation(shader, "a_UVCoord");
    if (uvloc != -1)
    {
        glVertexAttribPointer(uvloc, 2, GL_FLOAT, GL_FALSE, stride, (void*)8);
        glEnableVertexAttribArray(uvloc);
    }

    //Color
    GLint colorloc = glGetAttribLocation(shader, "a_ObjectColor");
    if (colorloc != -1)
    {
        glVertexAttribPointer(colorloc, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (void*)(sizeof(float) * 4));//(sizeof(float)*4) is used to account for the previously checked XY position, and UV position
        glEnableVertexAttribArray(colorloc);
    }
}

void ParticleRenderer::addParticle(Particle aParticle)
{
    //Check we aren't over the particle limit
    if (m_NumberOfParticles < PARTICLES_RENDERER_MAX_NUMBER_OF_PARTICLES)
    {

        Vector2 halfSize = aParticle.getSize() / 2;
        Vector2 particlePosition = aParticle.getPosition();// aParticle.getPosition();
        Vector4Int particleColor = aParticle.getColor();

        //Copy the data into the block of memory
        //m_blockOfMemory[m_NumberOfParticles * 4 + 0].Set( Vector2(position.x - 0.25, position.y + 0.25), Vector2(0,1) );
        m_blockOfMemory[m_NumberOfParticles * 4 + 0].fillVertexFormat(Vector2(particlePosition.x - halfSize.x, particlePosition.y + halfSize.y), Vector2(0.0f, 1.0f), particleColor);//Top Left
        m_blockOfMemory[m_NumberOfParticles * 4 + 1].fillVertexFormat(Vector2(particlePosition.x + halfSize.x, particlePosition.y + halfSize.y), Vector2(1.0f, 1.0f), particleColor);//Top right
        m_blockOfMemory[m_NumberOfParticles * 4 + 2].fillVertexFormat(Vector2(particlePosition.x + halfSize.x, particlePosition.y - halfSize.y), Vector2(1.0f, 0.0f), particleColor);//Bottom right
        m_blockOfMemory[m_NumberOfParticles * 4 + 3].fillVertexFormat(Vector2(particlePosition.x - halfSize.x, particlePosition.y - halfSize.y), Vector2(0.0f, 0.0f), particleColor);//Bottom Left

        //Update the variables data 
        m_NumberOfParticles++;
        m_NumberOfIndices = m_NumberOfParticles * 6;
    }
}

void ParticleRenderer::setTexture(GLuint aTexture)
{
    m_Texture = aTexture;
}