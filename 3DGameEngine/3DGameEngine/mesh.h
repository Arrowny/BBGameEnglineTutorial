#pragma once
#include <string>
#include <vector>
#include <GL\glew.h>
#include "vertex.h"
#include "resourceLoader.h"

class Mesh
{
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
	Mesh(const std::string meshFileName);
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
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	void initMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
};

