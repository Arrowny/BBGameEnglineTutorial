#pragma once
#include <GL\glew.h>
#include "vertex.h"

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	virtual ~Mesh();

	void Draw();

	enum
	{
		POSITION_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	unsigned int m_drawCount;

private:
	Mesh(const Mesh& other) {}
	void operator=(const Mesh& other) {}
};

