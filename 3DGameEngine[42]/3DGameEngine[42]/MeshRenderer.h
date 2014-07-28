#pragma once
#include "GameComponent.h"
#include "Mesh.h"
#include "BasicShader.h"

class MeshRenderer :public GameComponent
{
public:
	MeshRenderer(Mesh& mesh, Material& material)
	{
		m_mesh = &mesh;
		m_material = &material;
	}

	
	void render(Shader* m_shader, Transform* m_transform, RenderingEngine* renderingEngine)
	{
		m_shader->Bind();
		m_shader->Update(*m_transform, *renderingEngine, *m_material);
		m_material->m_texture->Bind(0);
		m_mesh->Draw();
	}

private:

	Mesh* m_mesh;
	Material* m_material;

};

