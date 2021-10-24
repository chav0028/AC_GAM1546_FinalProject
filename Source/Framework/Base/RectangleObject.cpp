/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : Draw a square

*/


#include "CommonHeader.h"

RectangleObject::RectangleObject(ShaderProgramIndex aIndexShaderProgram, Vector2 aScale, unsigned int aTextureIndex) :GameObject(aIndexShaderProgram, "Rectangle")
{
    setScale(aScale);//Set the scale

   m_IndexTextureToUse = aTextureIndex;
}

RectangleObject::~RectangleObject()
{
}

void RectangleObject::loadContent()
{
    //Get mesh
    setMesh(GameFramework::getInstance()->getResourcesManager()->getMesh(MESH_SQUARE_INDEX));

}