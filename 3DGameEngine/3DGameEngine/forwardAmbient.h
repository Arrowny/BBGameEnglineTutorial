#pragma once
#include "shader.h"
class ForwardAmbient :
	public Shader
{
public:
	ForwardAmbient(const std::string& fileName, glm::vec3 ambientLight);
	virtual ~ForwardAmbient();

	virtual std::string getShaderType() { return "FORWARD_AMBIENT_SHADER"; }
	virtual void updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat);

	glm::vec3 m_ambientIntensity;
};

