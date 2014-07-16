#pragma once

#include "gameComponent.h"
#include "Mesh.h"

class meshRenderer : public gameComponent
{
public:
	meshRenderer(Mesh& mesh, Material& material)
	{
		m_mesh = &mesh;
		m_material = &material;
	}

	virtual void render(Shader* shader, renderingEngine* renderingEngine)
	{
		shader->Bind();
		shader->Update(GetTransform(), *m_material, renderingEngine);
		m_mesh->Draw();
	}

protected:
private:
	Mesh*	  m_mesh;
	Material* m_material;
};