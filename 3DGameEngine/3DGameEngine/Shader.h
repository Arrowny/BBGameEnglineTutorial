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

class Shader
{
public:
	Shader();
	Shader(std::string& fileName);
	void Bind();//bind the shader, set the GPU in a state using vertex shader and frag shader in this class
	virtual void Update(Transform& transform,RenderingEngine& renderingEngine, Material& material) = 0;//        , DirectionalLight& directionalLight

	//virtual void UpdateUniforms(Transform& transform, Material& material, RenderingEngine* renderingEngine);

	//void SetAttribLocation(const std::string& attributeName, int location);
	//void SetUniformi(const std::string& name, int value);
	//void SetUniformf(const std::string& name, float value);
	//void SetUniform(const std::string& name, const glm::mat4& value);
	//void SetUniform(const std::string& name, const glm::vec3& value);

	virtual ~Shader();

protected:
	static const unsigned int NUM_SHADERS = 2;

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	enum
	{
		MVP,
		ambientIntensity,

		model,
		EYEPOS_U,
		L_SPECULARINTENSITY_U,
		L_SPECULARPOWER_U,

		L_DIRECTIONAL_BASE_COLOR_U,
		L_DIRECTIONAL_BASE_INTENSITY_U,
		L_DIRECTIONAL_DIRECTION_U,

		L_POINT_BASE_COLOR,
		L_POINT_BASE_INTENS,
		L_POINT_ATTEN_CONS,
		L_POINT_ATTEN_LINE,
		L_POINT_ATTEN_EXPO,
		L_POINT_POSITION,
		L_POINT_RANGE,

		L_SPOT_POINT_BASE_COLOR,
		L_SPOT_POINT_BASE_INTENS,
		L_SPOT_POINT_ATTEN_CONS,
		L_SPOT_POINT_ATTEN_LINE,
		L_SPOT_POINT_ATTEN_EXPO,
		L_SPOT_POINT_POSITION,
		L_SPOT_POINT_RANGE,
		L_SPOT_DIRECTION,
		L_SPOT_CUTOFF,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
	//std::map<std::string, UniformData> m_uniforms;

	//void AddShaderUniforms(const std::string& shaderText);
	//void AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs);
	//void AddAllAttributes(const std::string& vertexShaderText);

	//void AddProgram(const std::string& text, int type);
};


