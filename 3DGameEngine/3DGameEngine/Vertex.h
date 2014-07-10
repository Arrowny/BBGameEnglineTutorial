#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	int SIZE = 3;
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 1))//, const glm::vec2& texCoord
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* SetPos(glm::fvec3& pos) { this->pos = pos; }

	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal(){ return &normal; }
	inline void SetNormal(glm::fvec3& normal) { this->normal = normal; }

private:
	glm::vec3 pos;// variables: vertex attribute
	glm::vec2 texCoord;
	glm::vec3 normal;
};

