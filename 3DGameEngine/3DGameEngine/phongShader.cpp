#include "phongShader.h"
#include <iostream>
#include <sstream>



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

	for (int ii = 0; ii < MAX_POINT_LIGHTS; ii++)
	{
		std::ostringstream iteration;
		iteration << ii;

		addUniform("pointLights[" + iteration.str() + "].base.color");
		addUniform("pointLights[" + iteration.str() + "].base.intensity");
		addUniform("pointLights[" + iteration.str() + "].base.intensity");
		addUniform("pointLights[" + iteration.str() + "].atten.constant");
		addUniform("pointLights[" + iteration.str() + "].atten.linear");
		addUniform("pointLights[" + iteration.str() + "].atten.exponent");
		addUniform("pointLights[" + iteration.str() + "].position");
	}
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

void PhongShader::setUniform(std::string uniformName, Attenuation atten)
{
	setUniform(uniformName + ".constant", atten.m_constant);
	setUniform(uniformName + ".linear", atten.m_linear);
	setUniform(uniformName + ".exponent", atten.m_exponent);
}

void PhongShader::setUniform(std::string uniformName, PointLight pLight)
{
	setUniform(uniformName + ".base", pLight.m_base);
	setUniform(uniformName + ".atten", pLight.m_atten);
	setUniform(uniformName + ".position", pLight.m_position);
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
	
	for (int ii = 0; ii < m_pointLights.size(); ii++)
	{
		std::ostringstream iteration;
		iteration << ii;
		setUniform("pointlights[" + iteration.str() + "]", m_pointLights[ii]);
	}


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

void PhongShader::setPointLights(std::vector<PointLight> pointLights)
{
	if (pointLights.size() >= MAX_POINT_LIGHTS)
	{
		std::cerr << "Error: too many PointLights to be initialized.\n Max number of PointLights: " << MAX_POINT_LIGHTS << ".\n Number of PointLights sent in: " << pointLights.size() << "." << std::endl;
		exit(1);
	}

	m_pointLights = pointLights;
}




