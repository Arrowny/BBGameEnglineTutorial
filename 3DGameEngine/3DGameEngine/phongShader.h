#pragma once
#include "shader.h"
#include "Lights.h"
#include "camera.h"

#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4

class PhongShader :
	public Shader
{
public:
	PhongShader(const std::string& fileName, glm::vec3 ambientLight);
	~PhongShader();

	using Shader::setUniform;
	void setUniform(std::string uniformName, BaseLight base);
	void setUniform(std::string uniformName, DirectionalLight dLight);
	void setUniform(std::string uniformName, Attenuation atten);
	void setUniform(std::string uniformName, PointLight pLight);
	void setUniform(std::string uniformName, SpotLight sLight);

	virtual void updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat);
	//void setPointLights(std::vector<PointLight>* pointLights);
	//void setSpotLights(std::vector<SpotLight>* spotLights);
	
	glm::vec3 m_ambientLight;
	DirectionalLight m_dLight;

	std::vector<PointLight> m_pointLights;
	std::vector<SpotLight> m_spotLights;
};

