#pragma once
#include <glm\glm.hpp>

struct Vertex
{
	Vertex(const glm::vec3& pos)
	{
		this->pos = pos;
	}

	glm::vec3 pos;
};

