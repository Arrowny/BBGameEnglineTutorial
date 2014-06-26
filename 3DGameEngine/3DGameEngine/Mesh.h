#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void addVertices(const glm::fvec3 vertices);

protected:
private:

	int vbo;
	int size;

};

