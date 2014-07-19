#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Timing.h"
#include "Transform.h"
#include "directionalLight.h"
#include "baseLight.h"
#include "Material.h"
#include "pointLight.h"
#include "spotLight.h"
#include "renderingEngine.h"

class Shader
{
public:
	Shader();
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();
	void AddUniform(const std::string& uniform);
	void AddVertexShaderFromFile(const std::string& text);
	void AddGeometryShaderFromFile(const std::string& text);
	void AddFragmentShaderFromFile(const std::string& text);
	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void CompileShader();

	virtual void UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine);

	void SetAttribLocation(const std::string& attributeName, int location);
	void SetUniformi(const std::string& name, int value);
	void SetUniformf(const std::string& name, float value);
	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, const glm::fvec3& value);

protected:
	void AddShaderUniforms(const std::string& shaderText);
	void AddAllAttributes(const std::string& vertexShaderText);
	static std::string LoadShader(const std::string& fileName);
private:
	int m_program;
	std::map<std::string, int> m_uniforms;
	std::vector<int> m_shaders;

	void AddProgram(const std::string& text, int type);
	
};