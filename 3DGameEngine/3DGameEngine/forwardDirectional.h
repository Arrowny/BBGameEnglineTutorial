#pragma once
#include "shader.h"
#include "Lights.h"

class ForwardDirectional :
	public Shader
{
public:
	ForwardDirectional(std::string fileName);
	ForwardDirectional(std::string fileName, DirectionalLight dLight);
	virtual ~ForwardDirectional();

	using Shader::setUniform;
	void setUniform(std::string uniformName, BaseLight base);
	void setUniform(std::string uniformName, DirectionalLight dLight);

	virtual std::string getShaderType() { return "FORWARD_DIRECTIONAL_LIGHT_SHADER"; }
	virtual void updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat);

	DirectionalLight m_dLight;
};

