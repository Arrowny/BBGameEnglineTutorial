#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>

class ShaderResource
{
public:
	ShaderResource();
	virtual ~ShaderResource();

	GLuint getProgram();

	enum
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,

		NUM_SHADERS
	};

	std::unordered_map<std::string, GLint> m_uniforms;
	GLuint m_shaders[NUM_SHADERS];
	std::vector<std::string> uniformNames;
	std::vector<std::string> uniformTypes;

private:
	GLuint m_program;

};

