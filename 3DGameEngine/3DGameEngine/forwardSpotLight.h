#pragma once
#include "shader.h"
#include "Lights.h"

class ForwardSpotLight :
	public Shader
{
public:
	ForwardSpotLight(std::string fileName);
	ForwardSpotLight(std::string fileName, SpotLight sLight);
	virtual ~ForwardSpotLight();

	using Shader::setUniform;
	void setUniform(std::string uniformName, BaseLight base);
	void setUniform(std::string uniformName, Attenuation atten);
	void setUniform(std::string uniformName, PointLight pLight);
	void setUniform(std::string uniformName, SpotLight sLight);

	virtual std::string getShaderType() { return "FORWARD_SPOTLIGHT_SHADER"; }
	virtual void updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat);

	SpotLight m_sLight;
};

