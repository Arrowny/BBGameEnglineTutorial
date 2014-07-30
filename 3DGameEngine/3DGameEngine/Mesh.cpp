#include "Mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>

std::unordered_map<std::string, MeshData*> Mesh::meshResourceMap;

MeshData::MeshData(unsigned int drawcount)
{
	m_drawCount = drawcount;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
}


MeshData::~MeshData()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

GLuint MeshData::GetVAO()
{
	return m_vertexArrayObject;
}

GLuint MeshData::GetVAB(const unsigned int& BUFFER)
{
	return m_vertexArrayBuffers[BUFFER];
}

unsigned int MeshData::GetDrawCount()
{
	return m_drawCount;
}

Mesh::Mesh(const std::string& fileName){

	m_fileName = fileName;
	if (meshResourceMap.find(m_fileName) != meshResourceMap.end())
	{
		meshResourceMap[m_fileName]->AddReference();
	}
	else
	{
		InitMesh(OBJModel(fileName).ToIndexedModel());
	}
	

}

//Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, bool calcNormals)
//{
//	IndexedModel model;
//
//	if (calcNormals)
//		this->CalcNormals(model);
//
//	for (unsigned int i = 0; i < numVertices; i++)
//	{
//		model.positions.push_back(*vertices[i].GetPos());
//		model.texCoords.push_back(*vertices[i].GetTexCoord());
//		model.normals.push_back(*vertices[i].GetNormal());
//	}
//
//	for (unsigned int i = 0; i < numIndices; i++)
//		model.indices.push_back(indices[i]);
//
//	InitMesh(model);
//
//}

void Mesh::InitMesh(const IndexedModel& model){

	m_drawCount = model.indices.size();
	m_meshData = new MeshData(m_drawCount);

	glBindVertexArray(m_meshData->GetVAO());

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->GetVAB(POSITION_VB));
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->GetVAB(TEXCOORD_VB));
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshData->GetVAB(NORMAL_VB));
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshData->GetVAB(INDEX_VB));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	meshResourceMap[m_fileName] = m_meshData;

}

Mesh::~Mesh()
{
	if (meshResourceMap[m_fileName]->GetReferenceCount() == 0)
	{
		meshResourceMap.erase(m_fileName);
	}
	else
	{
		meshResourceMap[m_fileName]->RemoveReference();
	}
}

void Mesh::Draw()
{
	glBindVertexArray(meshResourceMap[m_fileName]->GetVAO());

	glDrawElementsBaseVertex(GL_TRIANGLES, meshResourceMap[m_fileName]->GetDrawCount(), GL_UNSIGNED_INT, 0, 0);

	glBindVertexArray(0);
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