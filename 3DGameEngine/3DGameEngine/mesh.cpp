#include "mesh.h"

void Mesh::initMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords)
{
	m_drawCount = indices.size();
	std::vector<glm::vec3> normals = calcNormals(vertices, indices);

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXTURE_VB]);
	glBufferData(GL_ARRAY_BUFFER, textCoords.size()*sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords)
{
	initMesh(vertices, indices, textCoords);
}

Mesh::Mesh(const std::string meshFileName)
{

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> textCoords;
	Loader::LoadMeshInfo("./res/object_files/box.obj", vertices, indices);
	initMesh(vertices, indices, textCoords);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<glm::vec3> Mesh::calcNormals(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices)
{
	std::vector<glm::vec3> normals;
	normals.reserve(vertices.size());

	for (int ii = 0; ii < vertices.size(); ii++)
	{
		normals.push_back(glm::vec3(0.0, 0.0, 0.0));
	}

	for (int ii = 0; ii < indices.size(); ii += 3)
	{
		int i0 = indices[ii];
		int i1 = indices[ii + 1];
		int i2 = indices[ii + 2];

		glm::vec3 v1 = vertices[i1] - vertices[i0];
		glm::vec3 v2 = vertices[i2] - vertices[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		normals[i0] += normal;
		normals[i1] += normal;
		normals[i2] += normal;
	}

	for (int ii = 0; ii < normals.size(); ii++)
	{
		normals[ii] = glm::normalize(normals[ii]);
	}

	return normals;
}
