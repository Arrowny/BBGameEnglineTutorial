#include "Mesh.h"


Mesh::Mesh()
{

	vbo = glGenBuffers();
	size = 0;

}


Mesh::~Mesh()
{
}

void Mesh::addVertices(const glm::fvec3 vertices){

}
