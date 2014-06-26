#include "Vertex.h"


Vertex::Vertex(glm::fvec3 pos):
m_pos(pos)
{
}


Vertex::~Vertex()
{
}

glm::fvec3 Vertex::getPos(){

	return m_pos;

}

void Vertex::setPos(glm::fvec3 pos){

	m_pos = pos;

}