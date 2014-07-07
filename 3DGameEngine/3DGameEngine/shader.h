#pragma once
#include <string>
#include <map>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "material.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();
	void addUniform(std::string uniform);

	void setUniform(std::string uniformName, GLint value);
	void setUniform(std::string uniformName, GLfloat value);
	void setUniform(std::string uniformName, glm::vec3 value);
	void setUniform(std::string uniformName, glm::vec4 value);
	void setUniform(std::string uniformName, glm::mat4 value);

	void updateBasicUniformsAndTexture(glm::mat4 projectionMatrix, glm::mat4 worldMatrix,Material* mat);

private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,

		NUM_SHADERS
	};

	std::map<std::string, GLint> m_uniforms;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

