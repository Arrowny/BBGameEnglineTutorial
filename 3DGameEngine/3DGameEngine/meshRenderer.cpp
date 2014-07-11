#include "meshRenderer.h"


MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) :
m_mesh(mesh),
m_material(material)
{
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Render(Transform transform)
{
	m_mesh->Draw();
}
