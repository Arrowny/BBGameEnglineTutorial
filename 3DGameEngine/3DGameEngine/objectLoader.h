#pragma once
#include <vector>
#include <string>
#include <glm\glm.hpp>

struct OBJIndex
{
public:
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;

	bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
	bool operator==(const OBJIndex& other)
	{
		return ((this->vertexIndex == other.vertexIndex) && (this->uvIndex == other.uvIndex) && (this->normalIndex == other.normalIndex));
	}

};

class IndexedModel
{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	IndexedModel() {}
	IndexedModel(const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texCoords, const std::vector<glm::vec3>& normals, const std::vector<unsigned int>& indices) :
		positions(positions),
		texCoords(texCoords),
		normals(normals),
		indices(indices){}

	void calcNormals();
};

class OBJModel
{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<OBJIndex> indices;

	OBJModel(std::string fileName);

	IndexedModel toIndexedModel();

private:
	OBJIndex parseIndex(std::string token);

	bool hasTexCoords = false;
	bool hasNormals = false;

	
};

class ObjectLoader
{
public:
	ObjectLoader();
	virtual ~ObjectLoader();
};

