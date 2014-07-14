#pragma once
#include "GameComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"


class MeshRenderer:public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Material* material);

		

	virtual void render(Transform transform);

	~MeshRenderer();

private:
	Mesh* m_mesh;
	Material* m_material;
};

