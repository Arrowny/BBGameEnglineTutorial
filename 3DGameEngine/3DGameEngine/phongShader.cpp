#include "phongShader.h"


PhongShader::PhongShader(const std::string& fileName, glm::vec3 ambientLight) :
Shader(fileName),
m_ambientLight(ambientLight)
{

	addUniform("ambientLight");
	
	addUniform("transformProjected");
	addUniform("transformWorld");
	addUniform("baseColor");
	addUniform("isTextured");

	addUniform("dLight.base.color");
	addUniform("dLight.base.intensity");
	addUniform("dLight.direction");
	
	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePos");
}


PhongShader::~PhongShader()
{
}

void PhongShader::setUniform(std::string uniformName, BaseLight base)
{
	setUniform(uniformName + ".color", base.m_color);
	setUniform(uniformName + ".intensity", base.m_intensity);
}

void PhongShader::setUniform(std::string uniformName, DirectionalLight dLight)
{
	setUniform(uniformName + ".base", dLight.m_base);
	setUniform(uniformName + ".direction", dLight.m_direction);
}

void PhongShader::updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat)
{

	setUniform("ambientLight", m_ambientLight);
	setUniform("baseColor", mat.m_color);
	
	setUniform("transformProjected", camera.getProjectionTransform()*worldMatrix);
	setUniform("transformWorld", worldMatrix);
	setUniform("dLight", m_dLight);

	setUniform("specularIntensity", mat.m_specularIntensity);
	setUniform("specularPower", mat.m_specularPower);
	setUniform("eyePos", camera.m_pos);
	

	if (mat.m_texture != NULL)
	{
		mat.m_texture->Bind(0); //TODO: update so that multiple textures can be bound
		setUniform("isTextured", true);
	}
	else
	{
		Util::unbindTexture();
		setUniform("isTextured", false);
	}
}




