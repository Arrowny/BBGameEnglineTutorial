#pragma once
#include "shader.h"
#include "directionalLight.h"
#include "camera.h"

class PhongShader :
	public Shader
{
public:
	PhongShader(const std::string& fileName, glm::vec3 ambientLight);
	~PhongShader();

	using Shader::setUniform;
	void setUniform(std::string uniformName, BaseLight base);
	void setUniform(std::string uniformName, DirectionalLight dLight);

	virtual void updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat);
	
	glm::vec3 m_ambientLight;
	DirectionalLight m_dLight;
};

