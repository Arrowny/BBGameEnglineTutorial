#pragma once

#include "gameComponent.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh& mesh, Material& material)
	{
		m_mesh = &mesh;
		m_material = &material;
	}

	virtual void render(Shader* shader, RenderingEngine* renderingEngine)
	{
		shader->Bind();
		shader->UpdateUniforms(GetTransform(), *m_material, renderingEngine);
		m_mesh->Draw();
	}

protected:
private:
	Mesh*	  m_mesh;
	Material* m_material;
};