#pragma once
#include <glm\glm.hpp>

class Vertex
{
public:
	Vertex(const glm::vec3& pos);
	virtual ~Vertex();

	inline glm::vec3* GetPos() { return &pos; }

private:
	glm::vec3 pos;
};

