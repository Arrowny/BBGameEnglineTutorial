#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"
#include "referenceCounter.h"
#include <map>

class MeshData : public ReferenceCounter
{
public:
	MeshData(int indexSize);
	virtual ~MeshData();

	inline unsigned int GetVBO() { return m_vbo; }
	inline unsigned int GetIBO() { return m_ibo; }
	inline int GetSize() { return m_size; }
protected:
private:
	MeshData(MeshData& other) {}
	void operator=(MeshData& other) {}

	unsigned int m_vbo;
	unsigned int m_ibo;
	int m_size;
};

struct Vertex
{
public:

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3* GetPos()		 { return &pos; }
	inline glm::vec2* GetTexCoord()	 { return &texCoord; }
	inline glm::vec3* GetNormal()	 { return &normal; }

};

class Mesh
{
public:
	Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, bool calcNormals = true);

	void Draw();

	virtual ~Mesh();
protected:
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	static std::map<std::string, MeshData*> s_resourceMap;

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		
		NUM_BUFFERS
	};

	void CalcNormals(IndexedModel model);
	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	std::string m_fileName;
	MeshData* m_meshData;

};

#endif

