/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : Contain the vertices, and  other data about a certain
shape.

December 21
-Changed Mesh, so that it doesn't belong to a GameObject .But rather
//it uses the properties of the game object being passed
*/

#include "CommonHeader.h"

Mesh::Mesh(MeshFormat aMeshFormat, std::string aName) :
m_MeshName(aName),
m_NumberOfVertices(aMeshFormat.m_NumberVertices),
m_NumberOfIndices(aMeshFormat.m_NumberIndices),
m_PrimitiveType(aMeshFormat.m_PrimitiveType),
m_CameraPosition(0.0f, 0.0f),
m_ProjectionScale(0.0f, 0.0f),
m_Size(aMeshFormat.m_Size),
m_VBO(0),
m_IBO(0)
{
    //Fill the VBO
    fillVBO(aMeshFormat.m_Vertices);

    //If there are indices
    if (m_NumberOfIndices > 0)
    {
        if (aMeshFormat.m_Indices != nullptr)
        {
            fillIBO(aMeshFormat.m_Indices);//Fill the ibo
        }
    }
}

Mesh::~Mesh()
{
    //Delete the buffers
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
}

void Mesh::draw(GameObject* aObjectDrawn, Vector2 aCameraPosition, Vector2 aProjectionScale)
{
    //Set the "camera" variables in order to use them (easier than passing) when setting the uniforms
    m_CameraPosition = aCameraPosition;
    m_ProjectionScale = aProjectionScale;

    if (m_NumberOfIndices > 0)//If we have indices draw the IBO
    {
        drawIBO(aObjectDrawn);
    }
    else//If we dont have indices, draw with VBO
    {
        drawVBO(aObjectDrawn);
    }
}

void Mesh::fillVBO(VertexFormat* aVerticesAttributes)
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated
    assert(m_VBO == 0);

    unsigned int sizeOfBuffer = (sizeof(VertexFormat)* m_NumberOfVertices);

    // gen and fill buffer with our attributes
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)sizeOfBuffer, aVerticesAttributes, GL_STATIC_DRAW);

    // check for errors
    CheckForGLErrors();
}

void Mesh::fillIBO(unsigned int* aIndices)
{
    //Generate the IBO
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);//Use element array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumberOfIndices, aIndices, GL_STATIC_DRAW);

    // check for errors
    CheckForGLErrors();
}

void Mesh::setAttributes(GameObject* aObjectDrawn)
{
    //Get and save the shader program
    GLuint shaderProgram = getAndUseShaderProgram(aObjectDrawn);

    GLsizei stride = sizeof(VertexFormat);//Save the size of the vertex format

    //Set attributes
    //Positon
    GLint posloc = glGetAttribLocation(shaderProgram, "a_Position");
    if (posloc != -1)
    {
        glVertexAttribPointer(posloc, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(posloc);
    }

    //UV Coords
    GLint uvloc = glGetAttribLocation(shaderProgram, "a_UVCoord");
    if (uvloc != -1)
    {
        glVertexAttribPointer(uvloc, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 2));//(sizeof(float)*2) is used to account for the previously checked XY position
        glEnableVertexAttribArray(uvloc);
    }

    //Color
    GLint colorloc = glGetAttribLocation(shaderProgram, "a_ObjectColor");
    if (colorloc != -1)
    {
        glVertexAttribPointer(colorloc, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (void*)(sizeof(float) * 4));//(sizeof(float)*4) is used to account for the previously checked XY position, and UV position
        glEnableVertexAttribArray(colorloc);
    }
}

void Mesh::setUniforms(GameObject* aObjectDrawn)
{
    if (aObjectDrawn != nullptr)
    {
        GLuint shaderProgram = getAndUseShaderProgram(aObjectDrawn);

        //Set the object scale uniform
        GLint objectsScaleLoc = glGetUniformLocation(shaderProgram, "u_ObjectScale");
        if (objectsScaleLoc != -1)//Check for valid location
        {
            glUniform2f(objectsScaleLoc, aObjectDrawn->getScale().x, aObjectDrawn->getScale().y);//Set scale according to its parent object
        }

        //Set the object position uniform
        GLint objectPositionLoc = glGetUniformLocation(shaderProgram, "u_ObjectPosition");
        if (objectPositionLoc != -1)//Check for valid location
        {
            glUniform2f(objectPositionLoc, aObjectDrawn->getPosition().x, aObjectDrawn->getPosition().y);//Set position according to its parent object
        }

        //Set the object rotation uniform
        GLint objectRotationLoc = glGetUniformLocation(shaderProgram, "u_ObjectRotation");
        float objectAngleRadian = aObjectDrawn->getAngle()*PI / 180;//Convert angle to radian, since the sin and cos functions in vertex shader use radians
        if (objectRotationLoc != -1)//Check for valid location
        {
            glUniform1f(objectRotationLoc, objectAngleRadian);//Set rotation according to the gameobject
        }

        //Set the camera position uniform  
        Vector2 inverseCameraPos = m_CameraPosition*-1;//Multiply by -1 to get inverse position
        GLint cameraPositionLoc = glGetUniformLocation(shaderProgram, "u_CameraPosition");
        if (cameraPositionLoc != -1)//Check for valid location
        {
            glUniform2f(cameraPositionLoc, inverseCameraPos.x, inverseCameraPos.y);//Camera position is passed in the draw function
        }

        //Set the projection scale uiform
        GLint projectionScaleLoc = glGetUniformLocation(shaderProgram, "u_ProjectionScale");
        if (projectionScaleLoc != -1)//Check for valid location
        {
            glUniform2f(projectionScaleLoc, m_ProjectionScale.x, m_ProjectionScale.y);//Projection scale is passed in the draw function
        }

        //Set the object color uniform
        GLint objectColorLoc = glGetUniformLocation(shaderProgram, "u_ObjectColor");
        Vector4Int objectColor = aObjectDrawn->getColor();//Save the colro from the game object
        if (objectColorLoc != -1)//Check for valid location
        {
            //Set the color according to the game object owner
            glUniform4f(objectColorLoc, (float)objectColor.x / MAX_NUM_COLORS, (float)objectColor.y / MAX_NUM_COLORS, (float)objectColor.z / MAX_NUM_COLORS, (float)objectColor.w / MAX_NUM_COLORS);
            //Divide by 255 to convert color back to 0 to 1 range.
            //Cast as float to ensure it can be in that range
        }

        //Set the object back color uniform (Used for animations ,etc)
        GLint objectBackColorLoc = glGetUniformLocation(shaderProgram, "u_ObjectBackColor");
        Vector4Int objectBackColor = aObjectDrawn->getBackColor();//Save the colro from the game object
        if (objectBackColorLoc != -1)//Check for valid location
        {
            //Set the color according to the game object owner
            glUniform4f(objectBackColorLoc, (float)objectBackColor.x / MAX_NUM_COLORS, (float)objectBackColor.y / MAX_NUM_COLORS, (float)objectBackColor.z / MAX_NUM_COLORS, (float)objectBackColor.w / MAX_NUM_COLORS);
            //Divide by 255 to convert color back to 0 to 1 range.
            //Cast as float to ensure it can be in that range
        }

        //Set animation time unifrom
        GLuint animationTimerLoc = glGetUniformLocation(shaderProgram, "u_AnimationTimer");
        if (animationTimerLoc != -1)
        {
            glUniform1f(animationTimerLoc, (float)aObjectDrawn->getAnimationTimer());//Animation time is set through a set function, callled possibly from an update method
        }

        //Set animation time unifrom
        GLuint animationTimeLoc = glGetUniformLocation(shaderProgram, "u_TotalAnimationTime");
        if (animationTimeLoc != -1)
        {
            glUniform1f(animationTimeLoc, aObjectDrawn->getAnimationTime());//Animation time is set through a set function, callled possibly from an update method
        }


        //Set animation time unifrom
        GLuint sizeLoc = glGetUniformLocation(shaderProgram, "u_ModelSize");
        if (sizeLoc != -1)
        {
            glUniform2f(sizeLoc, aObjectDrawn->getRadius() * 2, aObjectDrawn->getRadius() * 2);//Animation time is set through a set function, callled possibly from an update method
        }


        //If we have a texture
        GLuint texture = GameFramework::getInstance()->getResourcesManager()->getTexture(aObjectDrawn->getIndexTextureToUse());
        if (texture > 0)
        {
            //Bind and activate the the texture
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            useTexture(texture);

            //Set  texture uniform
            GLuint textureLoc = glGetUniformLocation(shaderProgram, "u_Texture");
            if (textureLoc != -1)
            {
                glUniform1i(textureLoc, 0);//Binds the texture to image unit 0.
            }

            //Set  UV offset  uniform
            GLuint uVOffscaleLoc = glGetUniformLocation(shaderProgram, "u_UVScale");
            if (uVOffscaleLoc != -1)
            {
                glUniform2f(uVOffscaleLoc, aObjectDrawn->getUVScale().x, aObjectDrawn->getUVScale().y);//The offset is obtained from a set function
            }

            //Set  UV scale  uniform
            GLuint uVOffsetLoc = glGetUniformLocation(shaderProgram, "u_UVOffset");
            if (uVOffsetLoc != -1)
            {
                glUniform2f(uVOffsetLoc, aObjectDrawn->getUVOffset().x, aObjectDrawn->getUVOffset().y);//The offset is obtained from a set function
            }
        }
    }
}

//Sets the uniforms and attributes, and call draw using the VBO
void Mesh::drawVBO(GameObject* aObjectDrawn)
{
    if (aObjectDrawn != nullptr)
    {
        //Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        GLuint texture = GameFramework::getInstance()->getResourcesManager()->getTexture(aObjectDrawn->getIndexTextureToUse());
        useTexture(texture);

        //Set attributes and uniforms
        setAttributes(aObjectDrawn);
        setUniforms(aObjectDrawn);

        // check for errors
        CheckForGLErrors();

        glDrawArrays(m_PrimitiveType, 0, m_NumberOfVertices);//Use triangles to make more complex shape
    }
}

//Sets the uniforms and attributes, and call draw using the IBO
void Mesh::drawIBO(GameObject* aObjectDrawn)
{
    if (aObjectDrawn != nullptr)
    {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);//Bind the IBO 
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO

        GLuint texture = GameFramework::getInstance()->getResourcesManager()->getTexture(aObjectDrawn->getIndexTextureToUse());
        useTexture(texture);

        //Set attributes and uniforms
        setAttributes(aObjectDrawn);
        setUniforms(aObjectDrawn);

        CheckForGLErrors();

        glDrawElements(m_PrimitiveType, m_NumberOfIndices, GL_UNSIGNED_INT, (void*)0);//Draw the IBO
    }
}

//Function to check if we have a texture,and bind it we have it
void Mesh::useTexture(GLuint aTexture)
{
    //if we have a texture
    if (aTexture > 0)
    {
        //Activate and bind the texture
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, aTexture);
    }
}

GLuint Mesh::getAndUseShaderProgram(GameObject* aObjectDrawn)
{
    //Get and save the shader program
    ShaderProgramIndex shaderIndex = aObjectDrawn->getIndexShaderProgramToUse();//Get the shader to use according to the index stored in game object
    ShaderProgram* shaderProgramClass = GameFramework::getInstance()->getResourcesManager()->getShaderProgram(shaderIndex);//get the basic shader program, not the program in it

    if (shaderProgramClass != nullptr)//Check that it is a valid shader program
    {
        GLuint shaderProgram = shaderProgramClass->m_Program;//Get the program that will be used from the shader

        // shader index stored in the object
        glUseProgram(shaderProgram);//Set program to use

        //Return the shader program
        return shaderProgram;
    }
    return 0;
}

//Not 100% accurate radius
float Mesh::getRadius()
{
    float radius = m_Size.x + m_Size.y;//Add both sizes, horizontal and vertical
    radius = radius / 2;//Divide both sizes by 2

    return radius;//Return the radius
}
