#pragma once
#include "shader.h"
#include "Lights.h"

class ForwardDirectional :
	public Shader
{
public:
	ForwardDirectional(std::string fileName);
	virtual ~ForwardDirectional();

	virtual std::string getShaderType() { return "FORWARD_DIRECTIONAL_LIGHT_SHADER"; }
	virtual void updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine);

protected:
	using Shader::setUniform;
	void setUniform(std::string uniformName, BaseLight base);
	void setUniform(std::string uniformName, DirectionalLight* dLight);
};

