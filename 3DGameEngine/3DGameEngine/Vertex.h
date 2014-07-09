#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	int SIZE = 3;
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)//
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* SetPos(glm::fvec3& vertex) { this->pos = vertex; }

	inline glm::vec2* GetTexCoord() { return &texCoord; }

private:
	glm::vec3 pos;// variables: vertex attribute
	glm::vec2 texCoord;

};

