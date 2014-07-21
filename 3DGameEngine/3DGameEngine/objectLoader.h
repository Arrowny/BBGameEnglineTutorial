#pragma once
#include <vector>
#include <string>
#include <glm\glm.hpp>

//not currently working. Bugs in loading normals/textures :(
struct OBJIndex
{
public:
	unsigned int vertexIndex = 0;
	unsigned int uvIndex = 0;
	unsigned int normalIndex = 0;

	bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
	bool operator==(const OBJIndex& other);
	unsigned int hashCode();

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
	std::vector<OBJIndex> OBJIndices;

	OBJModel(std::string fileName);

	IndexedModel toIndexedModel();

private:
	OBJIndex parseIndex(std::string token);
	unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result) const;

	bool hasTexCoords = false;
	bool hasNormals = false;

	
};

class ObjectLoader
{
public:
	ObjectLoader();
	virtual ~ObjectLoader();
};

