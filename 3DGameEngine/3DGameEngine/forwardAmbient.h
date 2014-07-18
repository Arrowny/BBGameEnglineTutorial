#pragma once
#include "shader.h"
class ForwardAmbient :
	public Shader
{
public:
	ForwardAmbient(const std::string& fileName, glm::vec3 ambientLight);
	virtual ~ForwardAmbient();

	virtual std::string getShaderType() { return "FORWARD_AMBIENT_SHADER"; }
	virtual void updateBasicUniformsAndTexture(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine);

	glm::vec3 m_ambientIntensity;
};

