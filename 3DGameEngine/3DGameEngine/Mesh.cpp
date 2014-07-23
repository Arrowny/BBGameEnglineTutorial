#include "Mesh.h"
#include <vector>

//MeshData::MeshData(int indexSize)
//{
//
//}

Mesh::Mesh()
{
	IndexedModel model = OBJModel("./res/plane.obj").ToIndexedModel();
	InitMesh(model);
}
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
		//model.normals.push_back(*vertices[i].GetNormal());
	}
	if (true)
		this->CalcNormals(model);

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
	/*POSITION PART*/
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);// make it thinks that this block of data is an array
	glBufferData(GL_ARRAY_BUFFER, model.indices.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);// put all vertices data in this array

	glEnableVertexAttribArray(0);// make opengl look at a non_sequential array as a sequential array of data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/*TEXTCOORS PART*/
	//glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); //m_vertexArrayBuffers is already a pointer, so not use &
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);// make it thinks that this block of data is an array
	glBufferData(GL_ARRAY_BUFFER, model.indices.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);// put all vertices data in this array

	glEnableVertexAttribArray(1);// make opengl look at a non_sequential array as a sequential array of data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	/*NORMAL PART*/
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);// make it thinks that this block of data is an array
	glBufferData(GL_ARRAY_BUFFER, model.indices.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);// put all vertices data in this array

	glEnableVertexAttribArray(2);// make opengl look at a non_sequential array as a sequential array of data
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

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

void Mesh::CalcNormals(Vertex* vertices, int numVertices, int* indices, int indexSize)
{
	for(int i = 0; i < indexSize; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 v1 = *vertices[i1].GetPos() - *vertices[i0].GetPos();
		glm::vec3 v2 = *vertices[i2].GetPos() - *vertices[i0].GetPos();

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		vertices[i0].SetNormal(*vertices[i0].GetNormal() + normal);
		vertices[i1].SetNormal(*vertices[i1].GetNormal() + normal);
		vertices[i2].SetNormal(*vertices[i2].GetNormal() + normal);
	}

	for (int i = 0; i < numVertices; i++)
		vertices[i].SetNormal(glm::normalize(*vertices[i].GetNormal()));

}

void Mesh::CalcNormals(IndexedModel model)
{
	for (unsigned int i = 0; i < model.indices.size(); i += 3)
	{
		int i0 = model.indices[i];
		int i1 = model.indices[i + 1];
		int i2 = model.indices[i + 2];

		glm::vec3 v1 = model.positions[i1] - model.positions[i0];
		glm::vec3 v2 = model.positions[i2] - model.positions[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		model.normals[i0] += normal;
		model.normals[i1] += normal;
		model.normals[i2] += normal;
	}

	for (unsigned int i = 0; i < model.positions.size(); i++)
		model.normals[i] = glm::normalize(model.normals[i]);
}