#pragma once
#include "shader.h"
class ForwardAmbient :
	public Shader
{
public:
	ForwardAmbient::ForwardAmbient(const std::string& fileName);
	virtual ~ForwardAmbient();

	virtual std::string getShaderType() { return "FORWARD_AMBIENT_SHADER"; }
	virtual void updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine);

};

