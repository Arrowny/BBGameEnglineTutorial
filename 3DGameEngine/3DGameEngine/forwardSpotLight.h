#pragma once
#include "shader.h"
#include "Lights.h"

class ForwardSpotLight :
	public Shader
{
public:
	ForwardSpotLight(std::string fileName);
	virtual ~ForwardSpotLight();

	using Shader::setUniform;
	void setUniform(std::string uniformName, Attenuation atten);
	void setUniform(std::string uniformName, SpotLight* sLight);

	virtual std::string getShaderType() { return "FORWARD_SPOTLIGHT_SHADER"; }
	virtual void updateBasicUniformsAndTexture(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine);
};

