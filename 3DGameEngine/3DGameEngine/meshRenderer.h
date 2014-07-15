#pragma once
#include "gameComponent.h"
#include <string>
#include "mesh.h"
#include "material.h"
#include "shader.h"

class MeshRenderer :
	public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Material material);
	virtual ~MeshRenderer();

	void Render(Shader* shader, RenderingEngine* renderingEngine);

private:
	MeshRenderer(const MeshRenderer& other) {}
	void operator=(const MeshRenderer& other) {}

	Mesh* m_mesh;
	Material m_material;
};

