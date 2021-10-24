/*
Student:    Alvaro Chavez Mixco
Date:       Monday, October 19 , 2015
course:     GAM1546-Games and Graphics Computations II
Professor:  Jimmy Lord
Purpose:    Generate the VBOs for the shapes and draw them using OpenGL.

October 4:
-GenerateSquare on Shapes.cpp now draws a square instead of a triangle.
-Added on Shapes.cpp the space on buffers and strides required for 4 floats that would represent colors.

October 5:
-Fixed GenerateCircle and DrawCircle, it currently uses constant values, on Shapes.cpp,
-Cleaned code in Shapes.cpp

October 10:
-Made functions GenerateEnemyShape and DrawEnemyShape in Shapes.cpp.

October 11:
-Made functions GenerateTargetShape and DrawTargetShape in Shapes.cpp.
-Made multiple constants in Shapes.cpp to store the number of vertices each shape has.
-Made functions GeneratePlayerShape and DrawPlayerShape on Shapes.cpp.
-Added the deletes for the new shapes VBOs and their respective game object pointers (player, target, and enem

*/

#include "CommonHeader.h"


//Constants for number of vertices, so that they can be used in generate and draw
//ALL BASIC SHAPES ARE MADE IN A -0.5 TO 0.5 SCALE, SO THAT THEY CAN BE EASILY SCALED
const unsigned int NUM_VERTICES_TRIANGLE = 3;//Obvious number, but made into costant to improve readability
const unsigned int NUM_VERTICES_SQUARE = 4;
const unsigned int NUM_INDICES_SQUARE = 6;
const float CIRCLE_RADIUS = 0.5f;
const unsigned int CIRCLE_SLICES = 36;//36 is just a value to have an actual circle, we can modify it to have different shapes (diamond,pentagon, etc).
const float POLYGON_RADIUS = 0.5f;
const Vector2 BASIC_SHAPERS_SIZE = Vector2(1, 1);//From -0.5 to 0.5 in x and y
const Vector4Int BASIC_SHAPES_DEFAULT_COLOR = Vector4Int(0, 255, 0, 255);//Made a pure green for easier debugging, this color is only intended for basic shapes which we intend to change color

//Player
const unsigned int NUM_VERTICES_PLAYER = 12;
const unsigned int NUM_INDICES_PLAYER = 24;
const Vector2 SIZE_PLAYER = Vector2(10.0f, 10.0f);//From -5 to 5
const Vector4Int PLAYER_DEFAULT_COLOR = Vector4Int(255, 255, 255, 255);//White

//Shield Icon
const unsigned int NUM_VERTICES_SHIELD_ICON = 14;
const unsigned int NUM_INDICES_SHIELD_ICON = 39;
const Vector2 SIZE_SHIELD_ICON = Vector2(1.0f, 1.0f);//From -0.5 to 0.5.
const Vector4Int SHIELD_ICON_DEFAULT_COLOR_CENTER = Vector4Int(0, 0, 255, 255);//blue
const Vector4Int SHIELD_ICON_DEFAULT_COLOR_OUTER = Vector4Int(50, 100, 255, 200);//light blue
const Vector4Int SHIELD_ICON_DEFAULT_COLOR_EDGES = Vector4Int(120, 255, 255, 150);//cyan

//Projectile
const unsigned int NUM_VERTICES_PROJECTILE = 13;
const unsigned int NUM_INDICES_PROJECTILE = 27;
const Vector2 SIZE_PROJECTILE = Vector2(4.0f, 4.0f);//From -2 to 2
const Vector4Int PROJECTILE_DEFAULT_COLOR = Vector4Int(254, 255, 64, 255);//Orange like
const Vector4Int PROJECTILE_DEFAULT_COLOR_EDGES = Vector4Int(254, 100, 64, 240);

//Enemy One
const unsigned int NUM_VERTICES_ENEMY_ONE = 28;
const unsigned int NUM_INDICES_ENEMY_ONE = 48;
const Vector2 SIZE_ENEMY_ONE = Vector2(10.0f, 10.0f);//From -5 to 5
const Vector4Int ENEMY_ONE_DEFAULT_COLOR = Vector4Int(170, 170, 170, 255);//Gray like

//Enemy Two
const unsigned int NUM_VERTICES_ENEMY_TWO = 16;
const unsigned int NUM_INDICES_ENEMY_TWO = 36;
const Vector2 SIZE_ENEMY_TWO = Vector2(12.0f, 12.0f);//From -6 to 6
const Vector4Int ENEMY_TWO_DEFAULT_COLOR = Vector4Int(10, 10, 10, 255);//Gray like

void getTriangleVertices(MeshFormat* aMeshFormat)
{

    // vertex information for triangle, it has Position, UVCoords, and color
    //Create vertex array
    aMeshFormat->m_Vertices = new VertexFormat[NUM_VERTICES_TRIANGLE];

    //Fill vertex array
    aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-0.5f, 0.5f), Vector2(0.0f, 0.0f), BASIC_SHAPES_DEFAULT_COLOR);//Top Left
    aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(0.9f, 0.0f), Vector2(0.5f, 1.0f), BASIC_SHAPES_DEFAULT_COLOR);//Middle Right
    aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(-0.5f, -0.5f), Vector2(1.0f, 0.0f), BASIC_SHAPES_DEFAULT_COLOR);//Bottom Left

    //Return all the values
    aMeshFormat->m_NumberVertices= NUM_VERTICES_TRIANGLE;
    aMeshFormat->m_PrimitiveType = GL_TRIANGLES;
    aMeshFormat->m_Size = BASIC_SHAPERS_SIZE;
}

void getSquareVertices(MeshFormat* aMeshFormat)
{
	// vertex format for position, UV, and color
	aMeshFormat->m_Vertices = new VertexFormat[NUM_VERTICES_SQUARE];

	//Fill vertex array
	aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-0.5, 0.5f), Vector2(0.0f, 1.0f), BASIC_SHAPES_DEFAULT_COLOR);//Top left
	aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f), BASIC_SHAPES_DEFAULT_COLOR);//Top right
	aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.5f, -0.5f), Vector2(1.0f, 0.0f), BASIC_SHAPES_DEFAULT_COLOR);//Bottom right
	aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(-0.5, -0.5f), Vector2(0.0f, 0.0f), BASIC_SHAPES_DEFAULT_COLOR);//Bottom left

	//Create the indices array and fill it (2 triangles to draw square
	aMeshFormat->m_Indices = new unsigned int[NUM_INDICES_SQUARE];//Create IBO

	//Fill indices array
	//Triangle 1
	aMeshFormat->m_Indices[0] = 0;
	aMeshFormat->m_Indices[1] = 1;
	aMeshFormat->m_Indices[2] = 2;

	// Triangle 2
	aMeshFormat->m_Indices[3] = 0;
	aMeshFormat->m_Indices[4] = 3;
	aMeshFormat->m_Indices[5] = 2;

	//Return all the values
	aMeshFormat->m_PrimitiveType = GL_TRIANGLES;
	aMeshFormat->m_NumberIndices = NUM_INDICES_SQUARE;
	aMeshFormat->m_NumberVertices = NUM_VERTICES_SQUARE;
	aMeshFormat->m_Size = BASIC_SHAPERS_SIZE;//From -0.5 to 0.5 in x and y
}

void getCircleVertices(MeshFormat* aMeshFormat)
{
	//Create vertex arrray
    aMeshFormat->m_Vertices = new VertexFormat[CIRCLE_SLICES + 2];
    int index = 0;
    
    aMeshFormat->m_Vertices[index].fillVertexFormat(Vector2(0, 0), Vector2(0.5f, 0.5f), BASIC_SHAPES_DEFAULT_COLOR);//Center of circle

	//Create variabels to use in circle equation
	float tempX = 0;
	float tempY = 0;
	float PiDouble = PI * 2;//Circle = 2 PI radians
	float angleSlice = PiDouble / (float)CIRCLE_SLICES;//Calculate the angle of each slice

    for (int i = 0; i < CIRCLE_SLICES; i++)
    {

        tempX = 0 + (CIRCLE_RADIUS * cos(i * angleSlice));//Calculates the x position by using the radius and cos, the 0 added represents the center of the circle
        tempY = 0 + (CIRCLE_RADIUS * sin(i * angleSlice)); // Calculates the y position by using the radius and cos, the 0 added represents the center of the circle

        index++;//Increase the index of element we will modify
        
        aMeshFormat->m_Vertices[index].fillVertexFormat(Vector2(tempX, tempY), Vector2(tempX + 0.5f, tempY + 0.5f), BASIC_SHAPES_DEFAULT_COLOR);

    }

    //Set the coordinates of the last point as 1,0 so we can close the  drawing  of the "circumference"
    index++;

    aMeshFormat->m_Vertices[index].fillVertexFormat(Vector2(CIRCLE_RADIUS, 0.0f), Vector2(1.0f, 0.5f), BASIC_SHAPES_DEFAULT_COLOR);

    //Return all the values
    aMeshFormat->m_NumberVertices = CIRCLE_SLICES + 2;
    aMeshFormat->m_PrimitiveType = GL_TRIANGLE_FAN;
    aMeshFormat->m_Size = Vector2(CIRCLE_RADIUS*2,CIRCLE_RADIUS*2);//From -0.5 to 0.5 in x and y (If circle radius is 0.5, so circle radius *2
}

//The arraywith number of sides should account for the +2 required for the starting and end of the array
//It isn't loaded in the resources manager by default
void getPolygonShapeVertices(unsigned int aSides, MeshFormat* aMeshFormat)
{
    unsigned int index = 0;

	//Create the vertex array
	aMeshFormat->m_Vertices= new VertexFormat[aSides+2];

	aMeshFormat->m_Vertices[index].fillVertexFormat(Vector2(0, 0), Vector2(0.5f, 0.5f), BASIC_SHAPES_DEFAULT_COLOR);//Center of polygon shape

    float tempX = 0;
    float tempY = 0;

    float PiDouble = PI * 2;//Circle = 2 PI radians
    float angleSlice = PiDouble / (float)aSides;//Calculate the angle of each slice

    for (unsigned int i = 0; i < aSides; i++)
    {

        tempX = 0 + (CIRCLE_RADIUS * cos(i * angleSlice));//Calculates the x position by using the radius and cos, the 0 added represents the center of the circle
        tempY = 0 + (CIRCLE_RADIUS * sin(i * angleSlice)); // Calculates the y position by using the radius and cos, the 0 added represents the center of the circle

        index++;//Increase the index of element we will modify

		aMeshFormat->m_Vertices[index].fillVertexFormat(Vector2(tempX, tempY), Vector2(tempX + 0.5f, tempY + 0.5f), BASIC_SHAPES_DEFAULT_COLOR);

    }

    //Set the coordinates of the last point as 1,0 so we can close the  drawing  of the "circumference"
    index++;

	aMeshFormat->m_Vertices[index].fillVertexFormat(Vector2(POLYGON_RADIUS, 0.0f), Vector2(1.0f, 0.5f), BASIC_SHAPES_DEFAULT_COLOR);

    //Return all the values
	aMeshFormat->m_NumberVertices = aSides + 2;
	aMeshFormat->m_PrimitiveType = GL_TRIANGLE_FAN;
	aMeshFormat ->m_Size= Vector2(POLYGON_RADIUS*2, POLYGON_RADIUS * 2);//Radius * 2 == total size of the shape
}

void getPlayerVertices(MeshFormat* aMeshFormat)
{
    //The player is a simple shape in order for it to work better with the circle to circle collision

    //Create the vertex array
    aMeshFormat->m_Vertices = new VertexFormat[NUM_VERTICES_PLAYER];

    //Fill the Vertices (COMMENTED ARE THE VERTICES THAT ARE ALSO PART OF THE LABELED SHAPE, BUT BECAUSE OF THE USE OF IBO THEY ARE NOT IN USE, UNCOMMENTING THEM WON'T GUARANTEE THE VBO WILL WORK, USE FOR REFEERENCE ONLY.
    //Engine
    //Top triangle square
    aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-5.0f, 4.0f), Vector2(0.0f, 0.8f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(-4.0f, 4.0f), Vector2(0.1f, 0.8f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(-4.0f, -4.0f), Vector2(0.1f, 0.2f), PLAYER_DEFAULT_COLOR);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-5.0f, 4.0f), Vector2(0.0f, 0.8f), PLAYER_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(-4.0f, -4.0f), Vector2(0.0f, 0.2f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(-5.0f, -4.0f), Vector2(0.0f, 0.2f), PLAYER_DEFAULT_COLOR);

    //Main Body
    //Top triangle square
    aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(-4.0f,  5.0f), Vector2(0.1f, 1.0f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(0.0f, 5.0f), Vector2(0.5f, 1.0f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(0.0f, -5.0f), Vector2(0.5f, 0.0f), PLAYER_DEFAULT_COLOR);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(-4.0f, 5.0f), Vector2(0.1f, 1.0f), PLAYER_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(0.0f, -5.0f), Vector2(0.5f, 0.0f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(-4.0f, -5.0f), Vector2(0.1f, 0.0f), PLAYER_DEFAULT_COLOR);

    //Front of ship
    //Top triangle
    //aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(0.0f, 5.0f), Vector2(0.5f, 1.0f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(5.0f, 1.5f), Vector2(1.0f, 0.65f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(0.0f, 1.5f), Vector2(0.5f, 0.65f), PLAYER_DEFAULT_COLOR);

    //Top triangle Square
    aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(0.0f, 1.5f), Vector2(0.5f, 0.65f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(5.0f, 1.5f), Vector2(1.0f, 0.65f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(5.0f, -1.5f), Vector2(1.0f, 0.35f), PLAYER_DEFAULT_COLOR);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(0.0f, 1.5f), Vector2(0.5f, 0.65f), PLAYER_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(5.0f, -1.5f), Vector2(1.0f, 0.35f), PLAYER_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(0.0f, -1.5f), Vector2(0.5f, 0.35f), PLAYER_DEFAULT_COLOR);

    //Bottom triangle
    //aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(0.0f, -1.5f), Vector2(0.5f, 0.35f), PLAYER_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(5.0f, -1.5f), Vector2(1.0f, 0.35f), PLAYER_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(0.0f, -5.0f), Vector2(0.5f, 0.0f), PLAYER_DEFAULT_COLOR);

    //Create the Indices array and fill it (2 triangles to draw square
    aMeshFormat->m_Indices = new unsigned int[NUM_INDICES_PLAYER];//Create IBO

    //FIll indices array

    //Engine
    //Top triangle square
    aMeshFormat->m_Indices[0] = 0;
    aMeshFormat->m_Indices[1] = 1;
    aMeshFormat->m_Indices[2] = 2;

    //Bottom triangle square
    aMeshFormat->m_Indices[3] = 0;
    aMeshFormat->m_Indices[4] = 2;
    aMeshFormat->m_Indices[5] = 3;

    //Main Body
    //Top triangle square
    aMeshFormat->m_Indices[6] = 4;
    aMeshFormat->m_Indices[7] = 5;
    aMeshFormat->m_Indices[8] = 6;

    //Bottom triangle square
    aMeshFormat->m_Indices[9] = 4;
    aMeshFormat->m_Indices[10] = 6;
    aMeshFormat->m_Indices[11] = 7;

    //Front of ship
    //Top triangle
    aMeshFormat->m_Indices[12] = 5;
    aMeshFormat->m_Indices[13] = 8;
    aMeshFormat->m_Indices[14] = 9;

    //Top triangle Square
    aMeshFormat->m_Indices[15] = 9;
    aMeshFormat->m_Indices[16] = 8;
    aMeshFormat->m_Indices[17] = 10;

    //Bottom triangle square
    aMeshFormat->m_Indices[18] = 9;
    aMeshFormat->m_Indices[19] = 10;
    aMeshFormat->m_Indices[20] = 11;

    //Bottom triangle
    aMeshFormat->m_Indices[21] = 11;
    aMeshFormat->m_Indices[22] = 10;
    aMeshFormat->m_Indices[23] = 6;

    //Return all the values
    aMeshFormat->m_PrimitiveType = GL_TRIANGLES;
    aMeshFormat->m_NumberIndices = NUM_INDICES_PLAYER;
    aMeshFormat->m_NumberVertices = NUM_VERTICES_PLAYER;
    aMeshFormat->m_Size = SIZE_PLAYER;//From -5 to 5 in x and y

}

void getShieldIconVertices(MeshFormat* aMeshFormat)
{
    //The player is a simple shape in order for it to work better with the circle to circle collision

    //Create the vertex array
    aMeshFormat->m_Vertices = new VertexFormat[NUM_VERTICES_SHIELD_ICON];

    //Fill the Vertices (COMMENTED ARE THE VERTICES THAT ARE ALSO PART OF THE LABELED SHAPE, BUT BECAUSE OF THE USE OF IBO THEY ARE NOT IN USE, UNCOMMENTING THEM WON'T GUARANTEE THE VBO WILL WORK, USE FOR REFEERENCE ONLY.
    //Main Shape-Made into 4 squares in order to be able to use varyings
    //Top Left Square
    //Top triangle square
    aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-0.5f, 0.5f), Vector2(0.1f, 1.0f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(0.0f, 0.5f), Vector2(0.5f, 1.0f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f), SHIELD_ICON_DEFAULT_COLOR_CENTER);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-0.5f, 0.5f), Vector2(0.1f, 1.0f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f), SHIELD_ICON_DEFAULT_COLOR_CENTER);
    aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(-0.5f, 0.15f), Vector2(0.0f, 0.65f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Top Right Square
    //Top triangle square
    //aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(0.0f, 0.5f), Vector2(0.5f, 1.0f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(0.5f, 0.15f), Vector2(1.0f, 0.65f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(0.0f, 0.5f), Vector2(0.5f, 1.0f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(0.5f, 0.15f), Vector2(1.0f, 0.65f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f), SHIELD_ICON_DEFAULT_COLOR_CENTER);

    //Bottom Right Square
    //Top triangle square
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f), SHIELD_ICON_DEFAULT_COLOR_CENTER);
    //aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(0.5f, 0.15f), Vector2(1.0f, 0.65f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(0.5f, -0.2f), Vector2(1.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f), SHIELD_ICON_DEFAULT_COLOR_CENTER);
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(0.5f, 0.2f), Vector2(1.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(0.0f, -0.2f), Vector2(0.5f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_OUTER);

    //Bottom Left Square
    //Top triangle square
    //aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(-0.5f, 0.15f), Vector2(0.0f, 0.65f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f), SHIELD_ICON_DEFAULT_COLOR_CENTER);
    //aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(0.0f, -0.2f), Vector2(0.5f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_OUTER);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(-0.5f, 0.15f), Vector2(0.0f, 0.65f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(0.0f, -0.2f), Vector2(0.5f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_OUTER);
    aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(-0.5f, -0.2f), Vector2(0.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Bottom part of shield
    //Left triangle
    //aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(-0.5f, -0.2f), Vector2(0.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(-0.4f, -0.2f), Vector2(0.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(-0.4f, -0.35f), Vector2(0.0f, 0.15f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Triangle Top Square
    //aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(-0.4f, -0.2f), Vector2(0.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_OUTER);
    aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(0.4f, -0.2f), Vector2(0.9f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(0.4f, -0.35f), Vector2(0.0f, 0.15f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Triangle Bottom Square
    //aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(-0.4f, -0.2f), Vector2(0.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_OUTER);
    //aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(0.4f, -0.35f), Vector2(0.0f, 0.15f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(-0.4f, -0.35f), Vector2(0.0f, 0.15f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Right triangle
    //aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(0.4f, -0.2f), Vector2(0.9f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_OUTER);
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(0.5f, 0.2f), Vector2(1.0f, 0.3f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(0.4f, -0.35f), Vector2(0.0f, 0.15f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Middle bottom triangle
    //aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(-0.4f, -0.35f), Vector2(0.0f, 0.15f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    //aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(0.4f, -0.35f), Vector2(0.0f, 0.15f), SHIELD_ICON_DEFAULT_COLOR_EDGES);
    aMeshFormat->m_Vertices[13].fillVertexFormat(Vector2(0.0f, -0.5f), Vector2(0.5f, 0.0f), SHIELD_ICON_DEFAULT_COLOR_EDGES);

    //Create the Indices array and fill it (2 triangles to draw square
    aMeshFormat->m_Indices = new unsigned int[NUM_INDICES_SHIELD_ICON];//Create IBO

    //FIll indices array

    //Main Shape-Made into 4 squares in order to be able to use varyings
    //Top Left Square
    //Top triangle square
    aMeshFormat->m_Indices[0] = 0;
    aMeshFormat->m_Indices[1] = 1;
    aMeshFormat->m_Indices[2] = 2;

    //Bottom triangle square
    aMeshFormat->m_Indices[3] = 0;
    aMeshFormat->m_Indices[4] = 2;
    aMeshFormat->m_Indices[5] = 3;

    //Top Right Square
    //Top triangle square
    aMeshFormat->m_Indices[6] = 1;
    aMeshFormat->m_Indices[7] = 4;
    aMeshFormat->m_Indices[8] = 5;

    //Bottom triangle square
    aMeshFormat->m_Indices[9] = 1;
    aMeshFormat->m_Indices[10] = 5;
    aMeshFormat->m_Indices[11] = 2;

    //Bottom Right Square
    //Top triangle square
    aMeshFormat->m_Indices[12] = 2;
    aMeshFormat->m_Indices[13] = 5;
    aMeshFormat->m_Indices[14] = 6;

    //Bottom triangle square
    aMeshFormat->m_Indices[15] = 2;
    aMeshFormat->m_Indices[16] = 6;
    aMeshFormat->m_Indices[17] = 7;

    //Bottom Left Square
    //Top triangle square
    aMeshFormat->m_Indices[18] = 3;
    aMeshFormat->m_Indices[19] = 2;
    aMeshFormat->m_Indices[20] = 7;

    //Bottom triangle square
    aMeshFormat->m_Indices[21] = 3;
    aMeshFormat->m_Indices[22] = 7;
    aMeshFormat->m_Indices[23] = 8;

    //Bottom part of shield
    //Left triangle
    aMeshFormat->m_Indices[24] = 8;
    aMeshFormat->m_Indices[25] = 9;
    aMeshFormat->m_Indices[26] = 10;

    //Triangle Top Square
    aMeshFormat->m_Indices[27] = 9;
    aMeshFormat->m_Indices[28] = 11;
    aMeshFormat->m_Indices[29] = 12;

    //Triangle Bottom Square
    aMeshFormat->m_Indices[30] = 9;
    aMeshFormat->m_Indices[31] = 12;
    aMeshFormat->m_Indices[32] = 10;

    //Right triangle
    aMeshFormat->m_Indices[33] = 11;
    aMeshFormat->m_Indices[34] = 6;
    aMeshFormat->m_Indices[35] = 12;

    //Middle bottom triangle
    aMeshFormat->m_Indices[36] = 10;
    aMeshFormat->m_Indices[37] = 12;
    aMeshFormat->m_Indices[38] = 13;

    //Return all the values
    aMeshFormat->m_PrimitiveType = GL_TRIANGLES;
    aMeshFormat->m_NumberIndices = NUM_INDICES_SHIELD_ICON;
    aMeshFormat->m_NumberVertices = NUM_VERTICES_SHIELD_ICON;
    aMeshFormat->m_Size = SIZE_SHIELD_ICON;//From -0.5 to 0.5 in x and y
}

//DOESN'T USE UV COORDINATES
void getProjectileVertices(MeshFormat * aMeshFormat)
{
	//Create the vertex array
	aMeshFormat->m_Vertices = new VertexFormat[NUM_VERTICES_PROJECTILE];

	//Fill the Vertices (COMMENTED ARE THE VERTICES THAT ARE ALSO PART OF THE LABELED SHAPE, BUT BECAUSE OF THE USE OF IBO THEY ARE NOT IN USE, UNCOMMENTING THEM WON'T GUARANTEE THE VBO WILL WORK, USE FOR REFEERENCE ONLY.
	//Top triangle
	aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(0.5f, 2.0f), Vector2(1.0f, 1.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-1.5f, 1.75f), Vector2(0.0f, 1.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.5f, 1.25f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);
	
	//Middle top triangle
	//aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(0.5f, 1.5f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);
	aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(-0.75f, 1.0f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	//aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(0.5f, 0.5f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);

	//Middle triangle
	//aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(0.5f, 0.5f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);
	aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(-2.0f, 0.0f), Vector2(0.0f, 0.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	//aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(0.5f, -0.5f), Vector2(0.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);

	//Middle bottom triangle
	//aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(0.5f, -0.5f), Vector2(0.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);
	aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(-0.75f, -1.0f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(0.5f, -1.25f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);

	//Bottom triangle
	//aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(0.5f, -1.25f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);
	aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(-1.5f, -1.75f), Vector2(1.0f, 1.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(0.5f, -2.0f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR_EDGES);

	//Right half "circle"
	//aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(0.5f, 2.0f), Vector2(1.0f, 1.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(2.0f, 0.5f), Vector2(0.0f, 0.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(0.5f, 0.5f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);
	aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(2.0f, -0.5f), Vector2(0.0f, 0.0f), PROJECTILE_DEFAULT_COLOR_EDGES);
	aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(0.5f, -0.5f), Vector2(0.0f, 0.0f), PROJECTILE_DEFAULT_COLOR);
	//aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(0.5f, -2.0f), Vector2(1.0f, 0.0f), PROJECTILE_DEFAULT_COLOR_EDGES);

	//Create the Indices array and fill it (2 triangles to draw square
	aMeshFormat->m_Indices = new unsigned int[NUM_INDICES_PROJECTILE];//Create IBO

	//FIll indices array
	//Top triangle
	aMeshFormat->m_Indices[0] = 0;
	aMeshFormat->m_Indices[1] = 1;
	aMeshFormat->m_Indices[2] = 2;

	//Middle top triangle
	aMeshFormat->m_Indices[3] = 5;
	aMeshFormat->m_Indices[4] = 2;
	aMeshFormat->m_Indices[5] = 4;

	//Middle triangle
	aMeshFormat->m_Indices[6] = 8;
	aMeshFormat->m_Indices[7] = 4;
	aMeshFormat->m_Indices[8] = 7;

	//Middle bottom triangle
	aMeshFormat->m_Indices[9] = 9;
	aMeshFormat->m_Indices[10] = 7;
	aMeshFormat->m_Indices[11] = 10;

	//Bottom triangle
	aMeshFormat->m_Indices[12] = 12;
	aMeshFormat->m_Indices[13] = 10;
	aMeshFormat->m_Indices[14] = 11;

	//Right half "circle"
	//Top triangle
	aMeshFormat->m_Indices[15] = 1;
	aMeshFormat->m_Indices[16] = 3;
	aMeshFormat->m_Indices[17] = 4;

	//Square top
	aMeshFormat->m_Indices[18] = 4;
	aMeshFormat->m_Indices[19] = 3;
	aMeshFormat->m_Indices[20] = 6;

	//Square bottom
	aMeshFormat->m_Indices[21] = 4;
	aMeshFormat->m_Indices[22] = 6;
	aMeshFormat->m_Indices[23] = 7;

	//Bottom triangle
	aMeshFormat->m_Indices[24] = 7;
	aMeshFormat->m_Indices[25] = 6;
	aMeshFormat->m_Indices[26] = 11;

	//Return all the values
	aMeshFormat->m_PrimitiveType = GL_TRIANGLES;
	aMeshFormat->m_NumberIndices = NUM_INDICES_PROJECTILE;
	aMeshFormat->m_NumberVertices = NUM_VERTICES_PROJECTILE;
	aMeshFormat->m_Size = SIZE_PROJECTILE;//From -2 to 2 in x and y
}

//DOESN'T USE UV COORDINATES
void getEnemyOneVertices(MeshFormat* aMeshFormat)
{
    //Create the vertex array
    aMeshFormat->m_Vertices = new VertexFormat[NUM_VERTICES_ENEMY_ONE];

    //Fill the Vertices (COMMENTED ARE THE VERTICES THAT ARE ALSO PART OF THE LABELED SHAPE, BUT BECAUSE OF THE USE OF IBO THEY ARE NOT IN USE, UNCOMMENTING THEM WON'T GUARANTEE THE VBO WILL WORK, USE FOR REFEERENCE ONLY.
    //Top "Wing"
    //Left triangle
    aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-5.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(-3.0f, 5.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);  
    aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(-3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);

    //bottom triangle square
    //aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(3.0f, 5.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);

    //top triangle square
    //aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(3.0f, 5.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(3.0f, 5.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //right triangle
    //aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(4.0f, 5.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(4.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(5.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //Top wing connection
    //top triangle square
    aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(-1.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(1.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(-1.0f, 2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //bottom triangle square
    aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(1.0f, 2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(1.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(-1.0f, 2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //Ship main body
    //Main square
    //Top triangle square
    aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(-2.0f, 2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(2.0f, 2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(-2.0f, -2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //bottom triangle square
    //aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(2.0f, 2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(-2.0f, -2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[13].fillVertexFormat(Vector2(2.0f, -2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //Front "cannons...?"
    //Top "cannon"
    //aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(2.0f, 2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[14].fillVertexFormat(Vector2(2.0f, 0.5f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[15].fillVertexFormat(Vector2(4.0f, 0.5f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //bottom cannon
    //aMeshFormat->m_Vertices[13].fillVertexFormat(Vector2(2.0f, -2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[16].fillVertexFormat(Vector2(2.0f, -0.5f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[17].fillVertexFormat(Vector2(4.0f, -0.5f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //Bottom wing connection
    //top triangle square
    aMeshFormat->m_Vertices[18].fillVertexFormat(Vector2(-1.0f, -2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[19].fillVertexFormat(Vector2(1.0f, -2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[20].fillVertexFormat(Vector2(1.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //bottom triangle square
    aMeshFormat->m_Vertices[21].fillVertexFormat(Vector2(-1.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[19].fillVertexFormat(Vector2(1.0f, -2.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[20].fillVertexFormat(Vector2(1.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //Bottom "Wing"
    //Left triangle
    aMeshFormat->m_Vertices[22].fillVertexFormat(Vector2(-5.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[23].fillVertexFormat(Vector2(-3.0f, -4.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[24].fillVertexFormat(Vector2(-3.0f, -5.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);

    //top triangle square
    //aMeshFormat->m_Vertices[23].fillVertexFormat(Vector2(-4.0f, -4.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[25].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[26].fillVertexFormat(Vector2(3.0f, -5.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);

    //bottom triangle square
    //aMeshFormat->m_Vertices[23].fillVertexFormat(Vector2(-3.0f, -4.0f), Vector2(1.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[24].fillVertexFormat(Vector2(-3.0f, -5.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[26].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);

    //right triangle
    //aMeshFormat->m_Vertices[25].fillVertexFormat(Vector2(-3.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[26].fillVertexFormat(Vector2(-3.0f, -5.0f), Vector2(1.0f, 0.0f), ENEMY_ONE_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[27].fillVertexFormat(Vector2(5.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_ONE_DEFAULT_COLOR);

    //Create the Indices array and fill it (2 triangles to draw square
    aMeshFormat->m_Indices = new unsigned int[NUM_INDICES_ENEMY_ONE];//Create IBO

    //FIll indices array

    //Top "Wing"
    //Left triangle
    aMeshFormat->m_Indices[0] = 0;
    aMeshFormat->m_Indices[1] = 1;
    aMeshFormat->m_Indices[2] = 2;

    //bottom triangle square
    aMeshFormat->m_Indices[3] = 1;
    aMeshFormat->m_Indices[4] = 4;
    aMeshFormat->m_Indices[5] = 2;

    //top triangle square
    aMeshFormat->m_Indices[6] = 1;
    aMeshFormat->m_Indices[7] = 3;
    aMeshFormat->m_Indices[8] = 4;

    //right triangle
    aMeshFormat->m_Indices[9] = 3;
    aMeshFormat->m_Indices[10] = 4;
    aMeshFormat->m_Indices[11] = 5;

    //Top wing connection
    //top triangle square
    aMeshFormat->m_Indices[12] = 6;
    aMeshFormat->m_Indices[13] = 7;
    aMeshFormat->m_Indices[14] = 8;

    //bottom triangle square
    aMeshFormat->m_Indices[15] = 8;
    aMeshFormat->m_Indices[16] = 7;
    aMeshFormat->m_Indices[17] = 9;

    //Ship main body
    //Main square
    //Top triangle square
    aMeshFormat->m_Indices[18] = 10;
    aMeshFormat->m_Indices[19] = 11;
    aMeshFormat->m_Indices[20] = 12;

    //bottom triangle square
    aMeshFormat->m_Indices[21] = 11;
    aMeshFormat->m_Indices[22] = 13;
    aMeshFormat->m_Indices[23] = 12;

    //Front "cannons...?"
    //Top "cannon"
    aMeshFormat->m_Indices[24] = 11;
    aMeshFormat->m_Indices[25] = 15;
    aMeshFormat->m_Indices[26] = 14;

    //bottom cannon
    aMeshFormat->m_Indices[27] = 16;
    aMeshFormat->m_Indices[28] = 17;
    aMeshFormat->m_Indices[29] = 13;

    //Bottom wing connection
    //top triangle square
    aMeshFormat->m_Indices[30] = 18;
    aMeshFormat->m_Indices[31] = 19;
    aMeshFormat->m_Indices[32] = 20;

    //bottom triangle square
    aMeshFormat->m_Indices[33] = 18;
    aMeshFormat->m_Indices[34] = 20;
    aMeshFormat->m_Indices[35] = 21;

    //Bottom "Wing"
    //Left triangle
    aMeshFormat->m_Indices[36] = 22;
    aMeshFormat->m_Indices[37] = 23;
    aMeshFormat->m_Indices[38] = 24;

    //top triangle square
    aMeshFormat->m_Indices[39] = 23;
    aMeshFormat->m_Indices[40] = 25;
    aMeshFormat->m_Indices[41] = 26;

    //bottom triangle square
    aMeshFormat->m_Indices[42] = 23;
    aMeshFormat->m_Indices[43] = 26;
    aMeshFormat->m_Indices[44] = 24;

    //right triangle
    aMeshFormat->m_Indices[45] = 25;
    aMeshFormat->m_Indices[46] = 27;
    aMeshFormat->m_Indices[47] = 26;

    //Return all the values
    aMeshFormat->m_PrimitiveType = GL_TRIANGLES;
    aMeshFormat->m_NumberIndices = NUM_INDICES_ENEMY_ONE;
    aMeshFormat->m_NumberVertices = NUM_VERTICES_ENEMY_ONE;
    aMeshFormat->m_Size = SIZE_ENEMY_ONE;//From -5 to 5 in x and y


}

//DOESN'T USE UV COORDINATES
void getEnemyTwoVertices(MeshFormat* aMeshFormat)
{

    //Create the vertex array
    aMeshFormat->m_Vertices = new VertexFormat[NUM_VERTICES_ENEMY_TWO];

    //Fill the Vertices (COMMENTED ARE THE VERTICES THAT ARE ALSO PART OF THE LABELED SHAPE, BUT BECAUSE OF THE USE OF IBO THEY ARE NOT IN USE, UNCOMMENTING THEM WON'T GUARANTEE THE VBO WILL WORK, USE FOR REFEERENCE ONLY.
    //Top "Wing"
    //botton triangle square
    aMeshFormat->m_Vertices[0].fillVertexFormat(Vector2(-6.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(-6.0f, 6.0f), Vector2(1.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Top triangle square
    //aMeshFormat->m_Vertices[1].fillVertexFormat(Vector2(-3.0f, 6.0f), Vector2(1.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(3.0f, 6.0f), Vector2(0.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Right triangle
    //aMeshFormat->m_Vertices[3].fillVertexFormat(Vector2(3.0f, 6.0f), Vector2(0.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[4].fillVertexFormat(Vector2(6.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Main body
    //Top triangle square
    aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(-3.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[5].fillVertexFormat(Vector2(-3.0f, 4.0f), Vector2(0.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[7].fillVertexFormat(Vector2(-3.0f, -4.0f), Vector2(0.0f, 1.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Front ship
    //Top triangle
    //aMeshFormat->m_Vertices[2].fillVertexFormat(Vector2(3.0f, 4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(5.0f, 1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(3.0f, 1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Top triangle square
    //aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(3.0f, 1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[8].fillVertexFormat(Vector2(5.0f, 1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(5.0f, -1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[9].fillVertexFormat(Vector2(3.0f, 1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(5.0f, -1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(3.0f, -1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Bottom triangle
    //aMeshFormat->m_Vertices[11].fillVertexFormat(Vector2(3.0f, -1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[10].fillVertexFormat(Vector2(5.0f, -1.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Bottom wing
    //Top triangle square
    aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(-6.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[13].fillVertexFormat(Vector2(3.0f, -6.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Bottom triangle square
    //aMeshFormat->m_Vertices[12].fillVertexFormat(Vector2(-6.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[13].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[14].fillVertexFormat(Vector2(-6.0f, -6.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Right triangle
    //aMeshFormat->m_Vertices[6].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    aMeshFormat->m_Vertices[15].fillVertexFormat(Vector2(6.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);
    //aMeshFormat->m_Vertices[13].fillVertexFormat(Vector2(3.0f, -4.0f), Vector2(1.0f, 0.0f), ENEMY_TWO_DEFAULT_COLOR);

    //Create the Indices array and fill it (2 triangles to draw square
    aMeshFormat->m_Indices = new unsigned int[NUM_INDICES_ENEMY_TWO];//Create IBO

    //FIll indices array

    //Top "Wing"
    //botton triangle square
    aMeshFormat->m_Indices[0] = 0;
    aMeshFormat->m_Indices[1] = 1;
    aMeshFormat->m_Indices[2] = 2;

    //Top triangle square
    aMeshFormat->m_Indices[3] = 1;
    aMeshFormat->m_Indices[4] = 3;
    aMeshFormat->m_Indices[5] = 2;

    //Right triangle
    aMeshFormat->m_Indices[6] = 3;
    aMeshFormat->m_Indices[7] = 4;
    aMeshFormat->m_Indices[8] = 2;

    //Main body
    //Top triangle square
    aMeshFormat->m_Indices[9] = 5;
    aMeshFormat->m_Indices[10] = 2;
    aMeshFormat->m_Indices[11] = 6;

    //Bottom triangle square
    aMeshFormat->m_Indices[12] = 5;
    aMeshFormat->m_Indices[13] = 6;
    aMeshFormat->m_Indices[14] = 7;

    //Front ship
    //Top triangle
    aMeshFormat->m_Indices[15] = 2;
    aMeshFormat->m_Indices[16] = 8;
    aMeshFormat->m_Indices[17] = 9;

    //Top triangle square
    aMeshFormat->m_Indices[18] = 9;
    aMeshFormat->m_Indices[19] = 8;
    aMeshFormat->m_Indices[20] = 10;

    //Bottom triangle square
    aMeshFormat->m_Indices[21] = 9;
    aMeshFormat->m_Indices[22] = 10;
    aMeshFormat->m_Indices[23] = 11;

    //Bottom triangle
    aMeshFormat->m_Indices[24] = 11;
    aMeshFormat->m_Indices[25] = 10;
    aMeshFormat->m_Indices[26] = 6;

    //Bottom wing
    //Top triangle square
    aMeshFormat->m_Indices[27] = 12;
    aMeshFormat->m_Indices[28] = 6;
    aMeshFormat->m_Indices[29] = 13;

    //Bottom triangle square
    aMeshFormat->m_Indices[30] = 12;
    aMeshFormat->m_Indices[31] = 13;
    aMeshFormat->m_Indices[32] = 14;

    //Right triangle
    aMeshFormat->m_Indices[33] = 6;
    aMeshFormat->m_Indices[34] = 15;
    aMeshFormat->m_Indices[35] = 13;

    //Return all the values
    aMeshFormat->m_PrimitiveType = GL_TRIANGLES;
    aMeshFormat->m_NumberIndices = NUM_INDICES_ENEMY_TWO;
    aMeshFormat->m_NumberVertices = NUM_VERTICES_ENEMY_TWO;
    aMeshFormat->m_Size = SIZE_ENEMY_TWO;//From -6 to 6 in x and y

}