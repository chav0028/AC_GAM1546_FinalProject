#ifndef __STRUCTS__H__
#define __STRUCTS__H__


/*
Student:    Alvaro Chavez Mixco
Date : Tuesday, December 14, 2015
course : GAM1546 - Games and Graphics Computations II
Professor : Jimmy Lord
Purpose : -Contains the types of structs normally used to have easy access to them

*/

//Struct containing all the attributes a single vertex has
struct VertexFormat
{
    float m_Position[2];
    float m_UV[2];
    unsigned char m_Color[4];

    void fillVertexFormat(Vector2 aPosition, Vector2 aUVCoord, Vector4Int aColor)
    {
        //Set position (center would be 0,0)
        m_Position[0] = aPosition.x;//X coordinate
        m_Position[1] = aPosition.y;//Y coordinate

        //Set UV coordinate (center would be 0.5, 0.5)
        m_UV[0] = aUVCoord.x;//U coordinate
        m_UV[1] = aUVCoord.y;//V coordinate

        //Set color
        m_Color[0] = (unsigned char)aColor.x;//Red
        m_Color[1] = (unsigned char)aColor.y;//Green
        m_Color[2] = (unsigned char)aColor.z;//Blue
        m_Color[3] = (unsigned char)aColor.w;//Alpha

    }
};

//Struct to store all the posible a mesh may need to be instantiated
struct MeshFormat
{
    VertexFormat* m_Vertices;
    unsigned int m_NumberVertices;
    GLenum m_PrimitiveType;
    Vector2 m_Size;
    unsigned int m_NumberIndices;
    unsigned int *m_Indices;

	void setMeshFormat() 
	{	
		//Set pointer to null
		m_Vertices = nullptr;
		m_Indices = nullptr;

		//Reset all the other stats
		m_NumberIndices = 0;
		m_NumberVertices = 0;
		m_PrimitiveType = 0;
		m_Size = Vector2(0.0f, 0.0f);
	}

	void resetMeshFormat()
	{
		//If there were vertices, delete them
		if (m_Vertices != nullptr)
		{
			delete[] m_Vertices;
		}
		
		//If there were indices delete them
		if (m_Indices != nullptr)
		{
			delete[] m_Indices;
		}

		setMeshFormat();//Set the default values again
	}

};


#endif