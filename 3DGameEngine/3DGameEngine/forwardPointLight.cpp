#include "forwardPointLight.h"



ForwardPointLight::ForwardPointLight(std::string fileName) :
Shader(fileName)
{
	addUniform("MVP");
	addUniform("model");
	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePos");

	addUniform("pLight.base.color");
	addUniform("pLight.base.intensity");
	addUniform("pLight.atten.constant");
	addUniform("pLight.atten.linear");
	addUniform("pLight.atten.exponent");
	addUniform("pLight.position");
	addUniform("pLight.range");
}

ForwardPointLight::~ForwardPointLight()
{
}

void ForwardPointLight::setUniform(std::string uniformName, Attenuation atten)
{
	setUniform(uniformName + ".constant", atten.m_constant);
	setUniform(uniformName + ".linear", atten.m_linear);
	setUniform(uniformName + ".exponent", atten.m_exponent);
}

void ForwardPointLight::setUniform(std::string uniformName, PointLight* pLight)
{
	setUniform(uniformName + ".atten", pLight->m_atten);
	setUniform(uniformName + ".base.color", pLight->m_color);
	setUniform(uniformName + ".base.intensity", pLight->m_intensity);
	setUniform(uniformName + ".position", pLight->getTransform()->m_trans);
	setUniform(uniformName + ".range", pLight->m_range);

}

void ForwardPointLight::updateBasicUniformsAndTexture(const glm::mat4& worldMatrix, const Material& mat, RenderingEngine* renderingEngine)
{
	setUniform("MVP", renderingEngine->getCamera()->getProjectionTransform()*worldMatrix);
	setUniform("model", worldMatrix);
	setUniform("eyePos", renderingEngine->getCamera()->m_pos);
	setUniform("specularIntensity", mat.m_specularIntensity);
	setUniform("specularPower", mat.m_specularPower);
	setUniform("pLight", (PointLight*)renderingEngine->activeLight);
}
