#pragma once
#include<glm/glm.hpp>
#include <GL/glew.h>
#include "Vertex.h"

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	void Draw();
	~Mesh();


private:
	enum
	{
		POSITION_VB,
		//TEXCOORD_VB,

		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

