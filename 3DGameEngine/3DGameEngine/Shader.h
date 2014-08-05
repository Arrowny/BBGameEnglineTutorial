#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Timing.h"
#include "Transform.h"
#include "Material.h"
#include "renderingEngine.h"
#include "referenceCounter.h"
#include "Lights.h"

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

class ShaderData : public ReferenceCounter
{
public:
	ShaderData();
	ShaderData(const std::string& fileName, const unsigned int&  shaderType);
	virtual ~ShaderData();

	inline int GetProgram() { return m_program; }
	inline std::vector<int>& GetShaders() { return m_shaders; }
	inline std::vector<std::string>& GetUniformNames() { return m_uniformNames; }
	inline std::vector<std::string>& GetUniformTypes() { return m_uniformTypes; }
	inline std::map<std::string, unsigned int>& GetUniformMap() { return m_uniformMap; }
protected:
	static std::string LoadShader(const std::string& fileName);
private:
	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void AddProgram(const std::string& text, int type);

	
	void AddShaderUniforms(const std::string& shaderText);
	void AddAllVaryings(const std::string& gsText);
	void AddAllAttributes(const std::string& vertexShaderText);
	void AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs);
	void CompileShader();

	int m_program;
	std::vector<int> m_shaders;
	std::vector<std::string> m_uniformNames;
	std::vector<std::string> m_uniformTypes;
	std::map<std::string, unsigned int> m_uniformMap;
};

class Shader
{
public:
	Shader();
	Shader(const std::string& fileName, const unsigned int& shaderType = 0);
	virtual ~Shader();

	void Bind();
	virtual void UpdateUniforms(const Transform& transform, PhysicsEngine* physicsEngine);
	virtual void UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine);

	void SetUniformi(const std::string& name, int value);
	void SetUniformf(const std::string& name, float value);
	void SetUniformMat4(const std::string& name, const glm::mat4& value);
	void SetUniformVec3(const std::string& name, const glm::fvec3& value);

	static enum
	{
		BASIC_SHADER_PIPELINE,
		FULL_SHADER_PIPELINE,
		PHYSICS_SHADER
	};

protected:

	void SetUniformDirectionalLight(const std::string& uniformName, const DirectionalLight& value);
	void SetUniformPointLight(const std::string& uniformName, const PointLight& value);
	void SetUniformSpotLight(const std::string& uniformName, const SpotLight& value);

private:
	static std::unordered_map<std::string, ShaderData*> shaderResourceMap;

	std::string m_fileName;

};