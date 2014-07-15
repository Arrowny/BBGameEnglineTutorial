#include "forwardSpotLight.h"


ForwardSpotLight::ForwardSpotLight(std::string fileName) :
Shader(fileName)
{
	addUniform("MVP");
	addUniform("model");
	addUniform("specularIntensity");
	addUniform("specularPower");
	addUniform("eyePos");

	addUniform("sLight.pLight.base.color");
	addUniform("sLight.pLight.base.intensity");
	addUniform("sLight.pLight.atten.constant");
	addUniform("sLight.pLight.atten.linear");
	addUniform("sLight.pLight.atten.exponent");
	addUniform("sLight.pLight.position");
	addUniform("sLight.pLight.range");
	addUniform("sLight.direction");
	addUniform("sLight.cutoff");
}

ForwardSpotLight::~ForwardSpotLight()
{
}

void ForwardSpotLight::setUniform(std::string uniformName, Attenuation atten)
{
	setUniform(uniformName + ".constant", atten.m_constant);
	setUniform(uniformName + ".linear", atten.m_linear);
	setUniform(uniformName + ".exponent", atten.m_exponent);
}

void ForwardSpotLight::setUniform(std::string uniformName, SpotLight* sLight)
{
	setUniform(uniformName + ".pLight.atten", sLight->m_atten);
	setUniform(uniformName + ".pLight.base.color", sLight->m_color);
	setUniform(uniformName + ".pLight.base.intensity", sLight->m_intensity);
	setUniform(uniformName + ".pLight.position", sLight->m_position);
	setUniform(uniformName + ".pLight.range", sLight->m_range);
	setUniform(uniformName + ".direction", sLight->m_direction);
	setUniform(uniformName + ".cutoff", sLight->m_cutoff);
}

void ForwardSpotLight::updateBasicUniformsAndTexture(const glm::mat4& worldMatrix, const Material& mat, RenderingEngine* renderingEngine)
{
	setUniform("MVP", renderingEngine->getCamera()->getProjectionTransform()*worldMatrix);
	setUniform("model", worldMatrix);
	setUniform("eyePos", renderingEngine->getCamera()->m_pos);
	setUniform("specularIntensity", mat.m_specularIntensity);
	setUniform("specularPower", mat.m_specularPower);
	setUniform("sLight", (SpotLight*)renderingEngine->activeLight);
}
