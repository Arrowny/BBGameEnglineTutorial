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

void ForwardDirectional::setUniform(std::string uniformName, DirectionalLight* dLight)
{
	setUniform(uniformName + ".base.color", dLight->m_color);
	setUniform(uniformName + ".base.intensity", dLight->m_intensity);
	setUniform(uniformName + ".direction", dLight->getDirection());
}

void ForwardDirectional::updateBasicUniformsAndTexture(const glm::mat4& worldMatrix, const Material& mat, RenderingEngine* renderingEngine)
{
	setUniform("MVP", renderingEngine->getCamera()->getProjectionTransform()*worldMatrix);
	setUniform("model", worldMatrix);
	setUniform("eyePos", renderingEngine->getCamera()->getTransform()->m_trans);
	setUniform("specularIntensity", mat.m_specularIntensity);
	setUniform("specularPower", mat.m_specularPower);
	setUniform("dLight", (DirectionalLight*)renderingEngine->activeLight);
}
