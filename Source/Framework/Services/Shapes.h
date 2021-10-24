#ifndef __SHAPES__H__
#define __SHAPES__H__

#include "Structs.h"

//Files with the vertices of all the objects:

//Basic shapes made from -0.5 to 0.5 range so that they easily scalable
void getTriangleVertices(MeshFormat* meshFormat);
void getSquareVertices(MeshFormat* meshFormat);
void getCircleVertices(MeshFormat* meshFormat);
void getPolygonShapeVertices( unsigned int sides, MeshFormat* meshFormat);//not loaded in resources manager by default

//Game shapes made in object space, relative to each other
void getPlayerVertices(MeshFormat* meshFormat);
void getShieldIconVertices(MeshFormat* meshFormat);
void getProjectileVertices(MeshFormat* meshFormat);
void getEnemyOneVertices(MeshFormat* meshFormat);
void getEnemyTwoVertices(MeshFormat* meshFormat);

#endif
