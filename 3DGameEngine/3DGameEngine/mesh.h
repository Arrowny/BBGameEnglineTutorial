#pragma once
#include <string>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "resourceLoader.h"
#include "util.h"
#include "meshResource.h"
#include "util.h"

class Mesh
{
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords);
	Mesh(const std::string meshFileName);
	virtual ~Mesh();

	void Draw();

	enum
	{
		POSITION_VB,
		INDEX_VB,
		TEXTURE_VB,
		NORMAL_VB,

		NUM_BUFFERS
	};

	MeshResource* m_meshResource;

private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	void initMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords);
	void initMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> textCoords, std::vector<glm::vec3> normals);
	std::vector<glm::vec3> calcNormals(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices);
	
	std::string m_fileName;
};

