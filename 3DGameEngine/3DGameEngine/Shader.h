#pragma once


#include <vector>
#include <string>
#include "Material.h"
#include "RenderingEngine.h"
#include "Transform.h"

//class RenderingEngine;
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

class ShaderData : public ReferenceCounter
{
public:
	ShaderData(const std::string& fileName);
	virtual ~ShaderData();

	inline int GetProgram() { return m_program; }
	inline std::vector<int>& GetShaders() { return m_shaders; }
	inline std::vector<std::string>& GetUniformNames() { return m_uniformNames; }
	inline std::vector<std::string>& GetUniformTypes() { return m_uniformTypes; }
	inline std::map<std::string, unsigned int>& GetUniformMap() { return m_uniformMap; }
private:
	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void AddProgram(const std::string& text, int type);

	void AddAllAttributes(const std::string& vertexShaderText);
	void AddShaderUniforms(const std::string& shaderText);
	void AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs);
	void CompileShader();


	std::map<std::string, unsigned int> m_uniformMap;

	int m_program;

	//std::map<std::string, UniformData> m_uniforms = std::map<std::string, UniformData>();
	std::vector<int> m_shaders;
	std::vector<std::string> m_uniformNames = std::vector<std::string>();
	std::vector<std::string> m_uniformTypes = std::vector<std::string>();
};
class Shader
{
public:
	Shader();
	Shader(const std::string& fileName);

	void Bind();//bind the shader, set the GPU in a state using vertex shader and frag shader in this class
	virtual void Update(Transform& transform, RenderingEngine& renderingEngine, Material& material);

	void SetAttribLocation(const std::string& attributeName, int location);
	void SetUniformi(const std::string& name, int value);
	void SetUniformf(const std::string& name, float value);
	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, const glm::vec3& value);

protected:

	void SetUniformDirectionalLight(const std::string& uniformName, const DirectionalLight& value);
	void SetUniformPointLight(const std::string& uniformName, const PointLight& value);
	void SetUniformSpotLight(const std::string& uniformName, const SpotLight& value);


	ShaderData* m_shaderData;
	std::string m_fileName;

	
};


