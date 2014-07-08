#include "phongShader.h"


PhongShader::PhongShader(const std::string& fileName, glm::vec3 ambientLight) :
Shader(fileName),
m_ambientLight(ambientLight)
{
	addUniform("ambientLight");
	addUniform("transform");
	addUniform("baseColor");
	addUniform("isTextured");
}


PhongShader::~PhongShader()
{
}

void PhongShader::updateBasicUniformsAndTexture(glm::mat4 projectionMatrix, glm::mat4 worldMatrix, Material* mat)
{
	setUniform("ambientLight", m_ambientLight);
	setUniform("baseColor", mat->m_color);
	setUniform("transform", projectionMatrix*worldMatrix);
	

	if (mat->m_texture != NULL)
	{
		mat->m_texture->Bind(0); //TODO: update so that multiple textures can be bound
		setUniform("isTextured", true);
	}
	else
	{
		Util::unbindTexture();
		setUniform("isTextured", false);
	}
}
