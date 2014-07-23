#pragma once
#include<glm/glm.hpp>
#include <GL/glew.h>
#include "Vertex.h"
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

class Mesh
{
public:
	Mesh();
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	void Draw();
	virtual ~Mesh();

	//inline void AddModel(const std::string& name, IndexedModel& value) { loadedModels.insert(std::pair<std::string, IndexedModel&>(name, value)); }

	//inline IndexedModel& GetModel(const std::string& name) const
	//{
	//	std::map<std::string, IndexedModel&>::const_iterator it = loadedModels.find(name);
	//	if (it != loadedModels.end())
	//		return it->second;

	//	return OBJModel("./res/plane.obj").ToIndexedModel();
	//}
private:
	static std::map<std::string, MeshData*> s_resourceMap;

	void InitMesh(const IndexedModel& model);
	void CalcNormals(Vertex* vertices, int numVertices, int* indices, int indexSize);
	void CalcNormals(IndexedModel model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	std::string m_fileName;
	MeshData* m_meshData;

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	//std::map<std::string, IndexedModel&> loadedModels = std::map<std::string, IndexedModel&>();
};

