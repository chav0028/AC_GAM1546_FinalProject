#ifndef __RESOURCESMANAGER__H__
#define __RESOURCESMANAGER__H__

#include <vector>

class ShaderProgram;
class Mesh;

const unsigned int NUMBER_FONT_SYSTEM_TEXTURE_INDEX = 0;
const unsigned int GAME_BACKGROUND_TEXTURE_INDEX = 1;
const unsigned int PLAYER_TEXTURE_INDEX = 2;
const unsigned int PARTICLE_TEXTURE_INDEX = 3;

const unsigned int MESH_TRIANGLE_INDEX = 0;
const unsigned int MESH_SQUARE_INDEX = 1;
const unsigned int MESH_CIRCLE_INDEX = 2;
const unsigned int MESH_PLAYER_INDEX = 3;
const unsigned int MESH_SHIELD_ICON_INDEX = 4;
const unsigned int MESH_PROJECTILE_INDEX = 5;
const unsigned int MESH_ENEMY_NORMAL_INDEX = 6;
const unsigned int MESH_ENEMY_BIG_INDEX = 7;

enum ShaderProgramIndex
{
    ShaderProgramIndex_FragBackColor = 0,
    ShaderProgramIndex_FragColor,
    ShaderProgramIndex_FragColorTexture,
    ShaderProgramIndex_Texture,
    ShaderProgramIndex_VaryingColor,
    ShaderProgramIndex_VaryingColorTexture,
    ShaderProgramIndex_VeticalFillInAnimation,
    ShaderProgramIndex_VeticalFillOutAnimation,
    ShaderProgramIndex_VertexEffect,
    ShaderProgramIndex_FragmentEffect,
    ShaderProgramIndex_VaryingColorEffect
};

/*Class to handle all the resources added in the game, such as shader programs, textures, meshes*/
class ResourcesManager
{
public:
    ResourcesManager();
    ~ResourcesManager();
    
    ShaderProgram* getShaderProgram(ShaderProgramIndex index = ShaderProgramIndex_FragColor);
    ShaderProgram* getActiveShaderProgram();

    Mesh* getMesh(unsigned int index);

    GLuint getTexture(unsigned int index);

    void addTexture(const char* fileName);
    void addShader(const char*vertfilename, const char* fragfilename);
    void addMesh(Mesh* mesh);

    void loadContent();

private:
    void loadShaders();
    void loadTextures();
    void loadMeshes();

    std::vector <GLuint> m_Textures;
    std::vector<ShaderProgram*>m_Shaders;
    std::vector <Mesh*> m_Meshes;
    ShaderProgramIndex m_ActiveShaderIndex;
};

#endif