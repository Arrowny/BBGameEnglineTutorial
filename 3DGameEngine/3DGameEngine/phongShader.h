#pragma once
#include "shader.h"
class PhongShader :
	public Shader
{
public:
	PhongShader(const std::string& fileName, glm::vec3 ambientLight);
	~PhongShader();

	virtual void updateBasicUniformsAndTexture(glm::mat4 projectionMatrix, glm::mat4 worldMatrix, Material* mat);
	
	glm::vec3 m_ambientLight;
};

