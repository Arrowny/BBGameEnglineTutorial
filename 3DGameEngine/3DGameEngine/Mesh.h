#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"
#include "referenceCounter.h"
#include <unordered_map>

enum
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB,

	NUM_BUFFERS
};

class MeshData : public ReferenceCounter
{
public:
	MeshData(unsigned int drawcount);
	virtual ~MeshData();

	GLuint GetVAO();
	GLuint GetVAB(const unsigned int& BUFFER);
	unsigned int GetDrawCount();

private:


	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	unsigned int m_drawCount;
};

class Mesh
{
public:
	Mesh(const std::string& fileName);

	void Draw();

	virtual ~Mesh();
protected:
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	void CalcNormals(IndexedModel model);
	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	std::string m_fileName;
	MeshData* m_meshData;

	static std::unordered_map<std::string, MeshData*> meshResourceMap;

};

#endif

