#include "meshRenderer.h"


MeshRenderer::MeshRenderer(Mesh* mesh, Material material, Shader* shader) :
m_mesh(mesh),
m_material(material),
m_shader(shader)
{
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Render(Transform* transform, Camera* camera)
{
	m_shader->Bind();
	m_shader->updateBasicUniformsAndTexture(*camera, transform->getTransformation(), m_material);
	m_mesh->Draw();
}
