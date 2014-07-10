#pragma once

#include "gameComponent.h"
#include "Mesh.h"
#include "Shader.h"

class meshRenderer : public gameComponent
{
public:
	meshRenderer(Mesh& mesh, Material& material, Camera& camera)
	{
		m_mesh = &mesh;
		m_material = &material;
		m_camera = &camera;
	}

	virtual void render(const Transform& transform, Shader* shader)
	{
		shader->Bind();
		shader->Update(transform, *m_camera, *m_material);
		m_material->texture->Bind(0);
		m_mesh->Draw();
	}

protected:
private:
	Mesh*	  m_mesh;
	Material* m_material;
	Camera*	  m_camera;
};