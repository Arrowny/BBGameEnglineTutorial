#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

struct Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this->pos = pos;
	}

	inline glm::vec3* GetPos() { return &pos; }
protected:
private:
	glm::vec3 pos;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();

	void Draw();

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};


	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	unsigned int m_drawCount;
};

