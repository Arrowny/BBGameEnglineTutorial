#include "mesh.h"
#include "obj_loader.h"

namespace
{
	IndexedModel LoadMeshInfo(const std::string& meshFileName)
	{
		std::vector<std::string> splitArray = Util::Split(meshFileName, '.');
		std::string extension = splitArray[splitArray.size() - 1];

		if (extension != "obj")
		{
			std::cerr << "Error: file extension \"" + extension + "\" is not supported " << std::endl;
			exit(1);
		}

		return OBJModel("./res/object_files/" + meshFileName).ToIndexedModel();
	}
};

void Mesh::initMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords)
{

	m_meshResource = new MeshResource(indices.size());
	std::vector<glm::vec3> normals = calcNormals(vertices, indices);

	glBindVertexArray(m_meshResource->getVAO());

	glBindBuffer(GL_ARRAY_BUFFER, m_meshResource->getVAB(POSITION_VB));
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshResource->getVAB(TEXTURE_VB));
	glBufferData(GL_ARRAY_BUFFER, textCoords.size()*sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshResource->getVAB(NORMAL_VB));
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshResource->getVAB(INDEX_VB));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::initMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords, std::vector<glm::vec3> normals)
{

	m_meshResource = new MeshResource(indices.size());

	glBindVertexArray(m_meshResource->getVAO());

	glBindBuffer(GL_ARRAY_BUFFER, m_meshResource->getVAB(POSITION_VB));
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshResource->getVAB(TEXTURE_VB));
	glBufferData(GL_ARRAY_BUFFER, textCoords.size()*sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshResource->getVAB(NORMAL_VB));
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshResource->getVAB(INDEX_VB));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	meshResourceMap[m_fileName] = m_meshResource;
}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords)
{
	m_fileName = "NOT_FROM_FILE";
	initMesh(vertices, indices, textCoords);
}

Mesh::Mesh(const std::string meshFileName)
{
	m_fileName = meshFileName;
	if (meshResourceMap.find(m_fileName) == meshResourceMap.end()) //only set up new mesh if mesh has not been created.
	{
		IndexedModel meshInfo = LoadMeshInfo(meshFileName);
		initMesh(meshInfo.positions, meshInfo.indices, meshInfo.texCoords, meshInfo.normals);
	}
	else
	{
		meshResourceCount[m_fileName]++;
	}
}

Mesh::~Mesh()
{
	if ( (meshResourceCount[m_fileName] == 0) && (m_fileName != "NOT_FROM_FILE") )
	{
		meshResourceMap.erase(m_fileName);
	}
	else if (m_fileName != "NOT_FROM_FILE")
	{
		meshResourceCount[m_fileName]--;
	}
}

void Mesh::Draw()
{
	if (m_fileName == "NOT_FROM_FILE")
	{
		glBindVertexArray(m_meshResource->getVAO());
		glDrawElements(GL_TRIANGLES, m_meshResource->getDrawCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(meshResourceMap[m_fileName]->getVAO());
		glDrawElements(GL_TRIANGLES, meshResourceMap[m_fileName]->getDrawCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
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
