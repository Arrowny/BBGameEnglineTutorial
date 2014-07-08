#pragma once
#include "shader.h"
#include "directionalLight.h"

class PhongShader :
	public Shader
{
public:
	PhongShader(const std::string& fileName, glm::vec3 ambientLight);
	~PhongShader();

	using Shader::setUniform;
	void setUniform(std::string uniformName, BaseLight base);
	void setUniform(std::string uniformName, DirectionalLight dLight);

	virtual void updateBasicUniformsAndTexture(glm::mat4 projectionMatrix, glm::mat4 worldMatrix, Material* mat);
	
	glm::vec3 m_ambientLight;
	DirectionalLight m_dLight;
};

