#include "meshRenderer.h"


MeshRenderer::MeshRenderer(Mesh* mesh, Material material) :
m_mesh(mesh),
m_material(material)
{
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Render(Transform* transform, Shader* shader, RenderingEngine* renderingEngine)
{
	shader->Bind();
	shader->updateBasicUniformsAndTexture(transform->getTransformation(), m_material, renderingEngine);
	m_mesh->Draw();
}
