#include "MeshRenderer.h"


MeshRenderer::MeshRenderer(Mesh* mesh, Material* material):
m_mesh(mesh),
m_material(material)
{}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(Transform transform)
{
	m_shader->Bind();
	m_shader->Update(*m_transform, *m_camera, *m_material);

	m_material->m_texture->Bind(0);
	m_mesh->Draw();
}