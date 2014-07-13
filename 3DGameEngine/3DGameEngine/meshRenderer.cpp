#include "meshRenderer.h"


MeshRenderer::MeshRenderer(Mesh* mesh, Material material) :
m_mesh(mesh),
m_material(material)
{
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Render(Transform* transform, Camera* camera, Shader* shader)
{
	shader->Bind();
	shader->updateBasicUniformsAndTexture(*camera, transform->getTransformation(), m_material);
	m_mesh->Draw();
}
