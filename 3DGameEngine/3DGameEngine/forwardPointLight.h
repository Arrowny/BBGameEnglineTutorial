#pragma once
#include "shader.h"
#include "Lights.h"

class ForwardPointLight :
	public Shader
{
public:
	ForwardPointLight(std::string fileName);
	ForwardPointLight(std::string fileName, PointLight pLight);
	virtual ~ForwardPointLight();

	using Shader::setUniform;
	void setUniform(std::string uniformName, BaseLight base);
	void setUniform(std::string uniformName, Attenuation atten);
	void setUniform(std::string uniformName, PointLight pLight);

	virtual std::string getShaderType() { return "FORWARD_POINTLIGHT_SHADER"; }
	virtual void updateBasicUniformsAndTexture(Camera& camera, const glm::mat4& worldMatrix, const Material& mat);

	PointLight m_pLight;
};

