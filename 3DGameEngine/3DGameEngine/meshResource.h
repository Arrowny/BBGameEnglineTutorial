#pragma once
#include <GL\glew.h>


class MeshResource
{
public:
	MeshResource(unsigned int drawcount);
	virtual ~MeshResource();

	GLuint getVAO();
	GLuint getVAB(const unsigned int& BUFFER);
	unsigned int getDrawCount();

private:
	enum
	{
		POSITION_VB,
		INDEX_VB,
		TEXTURE_VB,
		NORMAL_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	unsigned int m_drawCount;
};

