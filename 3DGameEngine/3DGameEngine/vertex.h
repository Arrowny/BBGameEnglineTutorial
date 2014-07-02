#pragma once
#include <glm\glm.hpp>

class Vertex
{
public:
	Vertex(const glm::vec3& pos);
	virtual ~Vertex();

	glm::vec3 pos;

private:
	
};

