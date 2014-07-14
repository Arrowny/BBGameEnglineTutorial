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

ForwardSpotLight::ForwardSpotLight(std::string fileName, SpotLight sLight) :
Shader(fileName),
m_sLight(sLight)
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

void ForwardSpotLight::setUniform(std::string uniformName, BaseLight base)
{
	setUniform(uniformName + ".color", base.m_color);
	setUniform(uniformName + ".intensity", base.m_intensity);
}

void ForwardSpotLight::setUniform(std::string uniformName, Attenuation atten)
{
	setUniform(uniformName + ".constant", atten.m_constant);
	setUniform(uniformName + ".linear", atten.m_linear);
	setUniform(uniformName + ".exponent", atten.m_exponent);
}

void ForwardSpotLight::setUniform(std::string uniformName, PointLight pLight)
{
	setUniform(uniformName + ".atten", pLight.m_atten);
	setUniform(uniformName + ".base", pLight.m_base);
	setUniform(uniformName + ".position", pLight.m_position);
	setUniform(uniformName + ".range", pLight.m_range);

}

void ForwardSpotLight::setUniform(std::string uniformName, SpotLight sLight)
{
	setUniform(uniformName + ".pLight", sLight.m_pLight);
	setUniform(uniformName + ".direction", sLight.m_direction);
	setUniform(uniformName + ".cutoff", sLight.m_cutoff);
}

void ForwardSpotLight::updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat)
{
	setUniform("MVP", camera.getProjectionTransform()*worldMatrix);
	setUniform("model", worldMatrix);
	setUniform("eyePos", camera.m_pos);
	setUniform("specularIntensity", mat.m_specularIntensity);
	setUniform("specularPower", mat.m_specularPower);
	setUniform("sLight", m_sLight);
}
