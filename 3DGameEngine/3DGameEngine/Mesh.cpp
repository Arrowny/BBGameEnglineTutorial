#include "Mesh.h"
#include <vector>


Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;

	glGenVertexArrays(1, &m_vertexArrayObject);// create space for vertex array
	glBindVertexArray(m_vertexArrayObject);// actual use it

	std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	//texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++){

		positions.push_back(*vertices[i].GetPos());
		//texCoords.push_back(*vertices[i].GetTexCoord());
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); //m_vertexArrayBuffers is already a pointer, so not use &
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);// make it thinks that this block of data is an array
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);// put all vertices data in this array

	glEnableVertexAttribArray(0);// make opengl look at a non_sequential array as a sequential array of data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	////glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); //m_vertexArrayBuffers is already a pointer, so not use &
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);// make it thinks that this block of data is an array
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);// put all vertices data in this array

	//glEnableVertexAttribArray(1);// make opengl look at a non_sequential array as a sequential array of data
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);// stop use it

}


Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);// actual use it

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}