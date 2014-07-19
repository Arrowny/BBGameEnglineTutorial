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

struct UniformData
{
	unsigned int Location;
	std::string Type;

	UniformData(unsigned int UniformLocation, const std::string& UniformType)
	{
		Location = UniformLocation;
		Type = UniformType;
	}
};

struct TypedData
{
	std::string name;
	std::string type;
};

struct UniformStruct
{
	std::string name;
	std::vector<TypedData> memberNames;
};

class Shader
{
public:
	Shader();
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();
	//void AddUniform(const std::string& uniform);
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
	void AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs);

	void SetUniformDirectionalLight(const std::string& uniformName, const directionalLight& value);
	void SetUniformPointLight(const std::string& uniformName, const pointLight& value);
	void SetUniformSpotLight(const std::string& uniformName, const spotLight& value);

private:
	int m_program;
	std::map<std::string, UniformData> m_uniforms;
	std::vector<int> m_shaders;
	std::vector<std::string> m_uniformNames;
	std::vector<std::string> m_uniformTypes;

	void AddProgram(const std::string& text, int type);
	
};