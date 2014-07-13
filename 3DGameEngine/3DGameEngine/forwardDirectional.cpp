#include "forwardDirectional.h"


ForwardDirectional::ForwardDirectional(std::string fileName) :
Shader(fileName)
{
	addUniform("MVP");
	addUniform("model");
	addUniform("eyePos");
	addUniform("specularIntensity");
	addUniform("specularPower");

	addUniform("dLight.base.color");
	addUniform("dLight.base.intensity");
	addUniform("dLight.direction");
	
}


ForwardDirectional::~ForwardDirectional()
{
}

void ForwardDirectional::setUniform(std::string uniformName, BaseLight base)
{
	setUniform(uniformName + ".color", base.m_color);
	setUniform(uniformName + ".intensity", base.m_intensity);
}

void ForwardDirectional::setUniform(std::string uniformName, DirectionalLight dLight)
{
	setUniform(uniformName + ".base", dLight.m_base);
	setUniform(uniformName + ".direction", dLight.m_direction);
}

void ForwardDirectional::updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat)
{
	setUniform("MVP", camera.getProjectionTransform()*worldMatrix);
	setUniform("model", worldMatrix);
	setUniform("eyePos", camera.m_pos);
	setUniform("specularIntensity", mat.m_specularIntensity);
	setUniform("specularPower", mat.m_specularPower);
	setUniform("dLight", m_dLight);
}
