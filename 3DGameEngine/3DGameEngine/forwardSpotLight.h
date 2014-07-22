#pragma once
#include "shader.h"
#include "Lights.h"

class ForwardSpotLight :
	public Shader
{
public:
	ForwardSpotLight(std::string fileName);
	virtual ~ForwardSpotLight();

	virtual std::string getShaderType() { return "FORWARD_SPOTLIGHT_SHADER"; }
	virtual void updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine);

protected:
	//using Shader::setUniform;
	//void setUniform(std::string uniformName, Attenuation atten);
	//void setUniform(std::string uniformName, SpotLight* sLight);
};

