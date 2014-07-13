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

	virtual void Init(Window* window, Transform* transform) {}
	virtual void ProcessInput(Input* input, Transform* transform) {}
	virtual void Update(Transform* transform) {}
	virtual void Render(Transform* transform, Camera* camera, Shader* shader);

private:
	MeshRenderer(const MeshRenderer& other) {}
	void operator=(const MeshRenderer& other) {}

	Mesh* m_mesh;
	Material m_material;
};

