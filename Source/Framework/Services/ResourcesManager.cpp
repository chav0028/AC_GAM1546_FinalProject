/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : se24 and get key presses

November 29;
-Now the resource manager is being loaded in the framework.
-All the shader are being worked in the resources manager.
-Additional bug fixes to mesh drawing.
-Added test component to Game scene.

December 1:
-Changed ResourcesManager to also handles the storage of meshes

December 6:
-Modified in ResourcesManager.CPP for the shaders to use a ShaderProgramIndex rather than indices of unsigned ints. 
This is to improve readability.
*/

#include "CommonHeader.h"

       using namespace std;

            ResourcesManager::ResourcesManager() :
                m_ActiveShaderIndex(ShaderProgramIndex_FragColor)
            {
            }

            ResourcesManager::~ResourcesManager()
            {
                //Delete all the shaders programs
                while (m_Shaders.empty() == false)
                {
                    //Delete the shader in the back
                    if (m_Shaders.back() != nullptr)
                    {
                        delete m_Shaders.back();
                        m_Shaders.back() = nullptr;
                    }
                    m_Shaders.pop_back();//Remove from vector
                }

                //Delete the meshes
                while (m_Meshes.empty() == false)
                {
                    //Delete the shader in the back
                    if (m_Meshes.back() != nullptr)
                    {
                        delete m_Meshes.back();
                        m_Meshes.back() = nullptr;
                    }
                    m_Meshes.pop_back();//Remove from vector
                }

                //Delete the textures
                while (m_Textures.empty() == false)
                {
                    //Delete the texture
                    glDeleteTextures(1, &m_Textures.back());

                    //Remove from vector
                    m_Textures.pop_back();
                }

            }

            void ResourcesManager::addTexture(const char* aFileName)
            {
                m_Textures.push_back(LoadTexture(aFileName));//Loads a texture and adds it to the vector
            }

            void ResourcesManager::addShader(const char* aVertfilename, const char*  aFragfilename)
            {
                m_Shaders.push_back(new ShaderProgram(aVertfilename, aFragfilename));//Add the shader program to the vector
            }

            void ResourcesManager::addMesh(Mesh* aMesh)
            {
                if (aMesh != nullptr)//If the mesh is not null
                {
                    m_Meshes.push_back(aMesh);//Add mesh to vector
                }
            }

            void ResourcesManager::loadContent()
            {
                //Load all the resources
                loadShaders();
                loadMeshes();
                loadTextures();
            }

            ShaderProgram* ResourcesManager::getShaderProgram(ShaderProgramIndex aIndex)
            {
                if (m_Shaders.empty() == false)//If we have shaders
                {
                    //Unsigned int can't be less than 0, so don't check for negative numbers

                    //If it is in a valid size
                    if ((unsigned int)aIndex < m_Shaders.size())
                    {
                        m_ActiveShaderIndex = aIndex;//Indicate that this is now the active shader
                        return m_Shaders.at(aIndex);//Return the shader
                    }
                }

                return nullptr;
            }

            ShaderProgram* ResourcesManager::getActiveShaderProgram()
            {
                if (m_Shaders.empty() == false)//If we have shaders
                {
                    //If it is in a valid size
                    if ((unsigned int)m_ActiveShaderIndex < m_Shaders.size())
                    {
                        return m_Shaders.at(m_ActiveShaderIndex);//Return the shader
                    }
                }

                return nullptr;//Return -1 to indicate error
            }

            GLuint ResourcesManager::getTexture(unsigned int aIndex)
            {
                if (aIndex < m_Textures.size())
                {
                    return m_Textures.at(aIndex);
                }

                return 0;
            }

            Mesh* ResourcesManager::getMesh(unsigned int aIndex)
            {
                if (aIndex < m_Meshes.size())
                {
                    return m_Meshes.at(aIndex);
                }

                return nullptr;
            }

            //Loads all the shaders
            void ResourcesManager::loadShaders()
            {
                addShader("Data/Shaders/FragBackColor.vert", "Data/Shaders/FragBackColor.frag");
                addShader("Data/Shaders/FragColor.vert", "Data/Shaders/FragColor.frag");
                addShader("Data/Shaders/FragColorTexture.vert", "Data/Shaders/FragColorTexture.frag");
                addShader("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag");
                addShader("Data/Shaders/VaryingColor.vert", "Data/Shaders/VaryingColor.frag");
                addShader("Data/Shaders/VaryingColorTexture.vert", "Data/Shaders/VaryingColorTexture.frag");
                addShader("Data/Shaders/VerticalFillInAnimation.vert", "Data/Shaders/VerticalFillInAnimation.frag");
                addShader("Data/Shaders/VerticalFillOutAnimation.vert", "Data/Shaders/VerticalFillOutAnimation.frag");

                addShader("Data/Shaders/VertexEffect.vert", "Data/Shaders/VertexEffect.frag");
                addShader("Data/Shaders/FragmentEffect.vert", "Data/Shaders/FragmentEffect.frag");
                addShader("Data/Shaders/VaryingColorEffect.vert", "Data/Shaders/VaryingColorEffect.frag");
            }

            //Loads all the textures
            void ResourcesManager::loadTextures()
            {
                addTexture("Data/Images/NumberFont.png");
                addTexture("Data/Images/Background.png");
                addTexture("Data/Images/Player.png");
                addTexture("Data/Images/Particle.png");
            }

            //Loads all the meshes
            void ResourcesManager::loadMeshes()
            {
                //Variables to store the content of a mesh
                MeshFormat meshProperties;
                meshProperties.setMeshFormat();

                //Triangle mesh
                //Get all the data required for the mesh
                getTriangleVertices(&meshProperties);//Fill the data of the mesh
                addMesh(new Mesh(meshProperties, "Triangle"));//Add the mesh to the resources manager
                meshProperties.resetMeshFormat();//Deletes the memory and reset stas

                //Square mesh
                //Get all the data required for the mesh
                getSquareVertices(&meshProperties);//Fill the data of the mesh
                addMesh(new Mesh(meshProperties, "Square"));//Add the mesh to the resources manager
                meshProperties.resetMeshFormat();

                //Circle mesh
                getCircleVertices(&meshProperties);//Fill the data of the mesh
                addMesh(new Mesh(meshProperties, "Circle"));//Add the mesh to the resources manager
                meshProperties.resetMeshFormat();

                //Player mesh
                getPlayerVertices(&meshProperties);
                addMesh(new Mesh(meshProperties, "Player"));
                meshProperties.resetMeshFormat();

                //Shield Icon mesh
                getShieldIconVertices(&meshProperties);
                addMesh(new Mesh(meshProperties, "ShieldIcon"));
                meshProperties.resetMeshFormat();

                //Projectile mesh
                getProjectileVertices(&meshProperties);
                addMesh(new Mesh(meshProperties, "Projectile"));
                meshProperties.resetMeshFormat();

                //Enemy one mesh
                getEnemyOneVertices(&meshProperties);
                addMesh(new Mesh(meshProperties, "EnemyOne"));
                meshProperties.resetMeshFormat();

                //Enemy two mesh
                getEnemyTwoVertices(&meshProperties);
                addMesh(new Mesh(meshProperties, "EnemyTwo"));
                meshProperties.resetMeshFormat();

            }