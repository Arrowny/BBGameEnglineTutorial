#pragma once
#include "shader.h"
#include "Lights.h"
#include "renderingEngine.h"


class ForwardPointLight :
	public Shader
{
public:
	ForwardPointLight(std::string fileName);
	virtual ~ForwardPointLight();

	virtual std::string getShaderType() { return "FORWARD_POINTLIGHT_SHADER"; }
	virtual void updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine);

protected:
	using Shader::setUniform;
	void setUniform(std::string uniformName, Attenuation atten);
	void setUniform(std::string uniformName, PointLight* pLight);
};

