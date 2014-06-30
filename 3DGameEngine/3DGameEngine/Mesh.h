#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this->pos = pos;
	}

	glm::vec3* GetPos() { return &pos; }

private:
	glm::vec3 pos;

};

class Mesh
{
public:
	Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void Draw();

	virtual ~Mesh();
protected:
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	enum
	{
		POSITION_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

};

#endif

