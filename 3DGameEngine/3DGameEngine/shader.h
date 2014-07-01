#pragma once
#include <string>
#include <GL\glew.h>

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();

private:
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,

		NUM_SHADERS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

