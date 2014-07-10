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
		std::ostringstream pointLightNameOSS;
		pointLightNameOSS << "pointLights[" << ii << "]";
		std::string pointLightName = pointLightNameOSS.str();
		
		addUniform(pointLightName + ".base.color");
		addUniform(pointLightName + ".base.intensity");
		addUniform(pointLightName + ".atten.constant");
		addUniform(pointLightName + ".atten.linear");
		addUniform(pointLightName + ".atten.exponent");
		addUniform(pointLightName + ".position");
		addUniform(pointLightName + ".range");
	}

	for (int ii = 0; ii < MAX_SPOT_LIGHTS; ii++)
	{
		std::ostringstream spotLightNameOSS;
		spotLightNameOSS << "spotLights[" << ii << "]";
		std::string spotLightName = spotLightNameOSS.str();

		addUniform(spotLightName + ".pLight.base.color");
		addUniform(spotLightName + ".pLight.base.intensity");
		addUniform(spotLightName + ".pLight.atten.constant");
		addUniform(spotLightName + ".pLight.atten.linear");
		addUniform(spotLightName + ".pLight.atten.exponent");
		addUniform(spotLightName + ".pLight.position");
		addUniform(spotLightName + ".pLight.range");
		addUniform(spotLightName + ".direction");
		addUniform(spotLightName + ".cutoff");
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
	setUniform(uniformName + ".atten", pLight.m_atten);
	setUniform(uniformName + ".base", pLight.m_base);
	setUniform(uniformName + ".position", pLight.m_position);
	setUniform(uniformName + ".range", pLight.m_range);
	
}

void PhongShader::setUniform(std::string uniformName, SpotLight sLight)
{
	setUniform(uniformName + ".pLight", sLight.m_pLight);
	setUniform(uniformName + ".direction", sLight.m_direction);
	setUniform(uniformName + ".cutoff", sLight.m_cutoff);
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
	
	if (m_pointLights.size() < MAX_POINT_LIGHTS)
	{ 
		for (int ii = 0; ii < m_pointLights.size(); ii++)
		{
			std::ostringstream pointLightNameOSS;
			pointLightNameOSS << "pointLights[" << ii << "]";
			std::string pointLightName = pointLightNameOSS.str();
			setUniform(pointLightName, m_pointLights[ii]);
		}
	}
	else
	{
		std::cerr << "Error: too many PointLights.\n Max number of PointLights: " << MAX_POINT_LIGHTS << ".\n Number of PointLights sent in: " << m_pointLights.size() << "." << std::endl;
		exit(1);
	}

	if (m_spotLights.size() < MAX_SPOT_LIGHTS)
	{ 
		for (int ii = 0; ii < m_spotLights.size(); ii++)
		{
			std::ostringstream spotLightNameOSS;
			spotLightNameOSS << "spotLights[" << ii << "]";
			std::string spotLightName = spotLightNameOSS.str();
			setUniform(spotLightName, m_spotLights[ii]);
		}
	}
	else
	{
		std::cerr << "Error: too many SpotLights.\n Max number of PointLights: " << MAX_SPOT_LIGHTS << ".\n Number of SpotLights sent in: " << m_spotLights.size() << "." << std::endl;
		exit(1);
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

//void PhongShader::setPointLights(std::vector<PointLight>* pointLights)
//{
//	if (pointLights->size() >= MAX_POINT_LIGHTS)
//	{
//		std::cerr << "Error: too many PointLights to be initialized.\n Max number of PointLights: " << MAX_POINT_LIGHTS << ".\n Number of PointLights sent in: " << pointLights->size() << "." << std::endl;
//		exit(1);
//	}
//
//	m_pointLights = pointLights;
//}
//
//void PhongShader::setSpotLights(std::vector<SpotLight>* spotLights)
//{
//	if (spotLights->size() >= MAX_SPOT_LIGHTS)
//	{
//		std::cerr << "Error: too many SpotLights to be initialized.\n Max number of PointLights: " << MAX_SPOT_LIGHTS << ".\n Number of SpotLights sent in: " << spotLights->size() << "." << std::endl;
//		exit(1);
//	}
//
//	m_spotLights = spotLights;
//}




