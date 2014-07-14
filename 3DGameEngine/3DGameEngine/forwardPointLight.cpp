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

ForwardPointLight::ForwardPointLight(std::string fileName, PointLight pLight) :
Shader(fileName),
m_pLight(pLight)
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

void ForwardPointLight::setUniform(std::string uniformName, BaseLight base)
{
	setUniform(uniformName + ".color", base.m_color);
	setUniform(uniformName + ".intensity", base.m_intensity);
}

void ForwardPointLight::setUniform(std::string uniformName, Attenuation atten)
{
	setUniform(uniformName + ".constant", atten.m_constant);
	setUniform(uniformName + ".linear", atten.m_linear);
	setUniform(uniformName + ".exponent", atten.m_exponent);
}

void ForwardPointLight::setUniform(std::string uniformName, PointLight pLight)
{
	setUniform(uniformName + ".atten", pLight.m_atten);
	setUniform(uniformName + ".base", pLight.m_base);
	setUniform(uniformName + ".position", pLight.m_position);
	setUniform(uniformName + ".range", pLight.m_range);

}

void ForwardPointLight::updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat)
{
	setUniform("MVP", camera.getProjectionTransform()*worldMatrix);
	setUniform("model", worldMatrix);
	setUniform("eyePos", camera.m_pos);
	setUniform("specularIntensity", mat.m_specularIntensity);
	setUniform("specularPower", mat.m_specularPower);
	setUniform("pLight", m_pLight);
}
