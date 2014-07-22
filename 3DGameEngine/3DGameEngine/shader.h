#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <utility>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "material.h"
#include "util.h"
#include "camera.h"
#include "renderingEngine.h"
#include "Lights.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();

	virtual std::string getShaderType() = 0;
	virtual void updateUniforms(const glm::mat4& worldMatrix, Material& mat, RenderingEngine* renderingEngine);

protected:
	void setUniform(std::string uniformName, GLint value);
	void setUniform(std::string uniformName, GLfloat value);
	void setUniform(std::string uniformName, glm::vec3 value);
	void setUniform(std::string uniformName, glm::vec4 value);
	void setUniform(std::string uniformName, glm::mat4 value);
	void setUniform(std::string uniformName, Attenuation atten);
	void setUniform(std::string uniformName, DirectionalLight* dLight);
	void setUniform(std::string uniformName, PointLight* pLight);
	void setUniform(std::string uniformName, SpotLight* sLight);

private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	void addAllUniforms(std::string shaderText, std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > structMap);
	void addUniform(std::string uniform);
	void addUniform(std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > structMap, std::string structName, std::string structType);

	std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > findUniformStructs(std::string shaderText);
	std::vector<std::string> addUniformHelper(std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > > structMap, std::string structName, std::string structType);

	enum
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,

		NUM_SHADERS
	};

	std::map<std::string, GLint> m_uniforms;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	std::vector<std::string> uniformNames;
	std::vector<std::string> uniformTypes;
};

