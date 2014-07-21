#include "meshResource.h"


MeshResource::MeshResource(unsigned int drawcount)
{
	m_drawCount = drawcount;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
}


MeshResource::~MeshResource()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

GLuint MeshResource::getVAO()
{
	return m_vertexArrayObject;
}

GLuint MeshResource::getVAB(const unsigned int& BUFFER)
{
	return m_vertexArrayBuffers[BUFFER];
}

unsigned int MeshResource::getDrawCount()
{
	return m_drawCount;
}