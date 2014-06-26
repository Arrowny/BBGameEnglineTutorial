#pragma once

#include <glm\glm.hpp>

class Vertex
{
public:
	Vertex(glm::fvec3 pos);
	~Vertex();

	glm::fvec3 getPos();
	void setPos(glm::fvec3 pos);

	static const int SIZE = 3;

protected:
private:

	glm::fvec3	m_pos;
	
};

