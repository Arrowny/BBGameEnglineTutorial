#include "Mesh.h"
#include <vector>


Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;


	glGenVertexArrays(1, &m_vertexArrayObject);// create space for vertex array
	glBindVertexArray(m_vertexArrayObject);// actual use it

	//std::vector<glm::vec3> positions;
	////std::vector<glm::vec2> texCoords;

	//model.positions.reserve(numVertices);
	////texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++){

		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}
	for (unsigned int i = 0; i < numIndices; i++){
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);

}


Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); //m_vertexArrayBuffers is already a pointer, so not use &
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);// make it thinks that this block of data is an array
	glBufferData(GL_ARRAY_BUFFER, model.indices.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);// put all vertices data in this array

	glEnableVertexAttribArray(0);// make opengl look at a non_sequential array as a sequential array of data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	//glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); //m_vertexArrayBuffers is already a pointer, so not use &
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);// make it thinks that this block of data is an array
	glBufferData(GL_ARRAY_BUFFER, model.indices.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);// put all vertices data in this array

	glEnableVertexAttribArray(1);// make opengl look at a non_sequential array as a sequential array of data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);// array of element consisting of data in the other arrays
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);// stop use it
}
void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);// actual use it

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}