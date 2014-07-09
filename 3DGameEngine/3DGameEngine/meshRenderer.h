#pragma once

#include "gameComponent.h"
#include "Mesh.h"
#include "Shader.h"

class meshRenderer : public gameComponent
{
public:
	meshRenderer(Mesh& mesh, Material& material, Shader& shader)
	{
		m_mesh = &mesh;
		m_material = &material;
		m_shader = &shader;
	}

	virtual void render(const Transform& transform)
	{
		m_shader->Bind();
		m_material->texture->Bind(0);
		m_mesh->Draw();
	}

protected:
private:
	Mesh*	  m_mesh;
	Material* m_material;
	Shader*	  m_shader;
};