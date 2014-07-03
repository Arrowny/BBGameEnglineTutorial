#include "shader.h"
#include "resourceLoader.h"
#include <iostream>

namespace
{
	//static std::string LoadShader(const std::string& fileName)
	//{
	//	std::ifstream file;
	//	file.open(fileName.c_str());

	//	std::string output;
	//	std::string line;

	//	if (file.is_open())
	//	{
	//		while (file.good())
	//		{
	//			getline(file, line);
	//			output.append(line + "\n");
	//		}
	//	}
	//	else
	//	{
	//		std::cerr << "File Readin Error: unable to load shader" << std::endl;
	//	}

	//	return output;
	//}

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 1 };

		if (isProgram)
		{
			glGetProgramiv(shader, flag, &success);
		}
		else
		{
			glGetShaderiv(shader, flag, &success);
		}

		if (success == GL_FALSE)
		{
			if (isProgram)
			{
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			}
			else
			{
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			}

			std::cerr << errorMessage << ": " << error << "." << std::endl;
		}
	}

	static GLuint CreateShader(const std::string& text, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		if (shader == 0)
		{
			std::cerr << " Error: Shader creation failed." << std::endl;
		}

		const GLchar* shaderSourceStrings[1];
		GLint ShaderSourceStringsLengths[1];

		shaderSourceStrings[0] = text.c_str();
		ShaderSourceStringsLengths[0] = text.size();

		glShaderSource(shader, 1, shaderSourceStrings, ShaderSourceStringsLengths);
		glCompileShader(shader);

		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader creation failure");

		return shader;
	}
};

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();

	m_shaders[VERTEX_SHADER] = CreateShader(Loader::LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	m_shaders[FRAGMENT_SHADER] = CreateShader(Loader::LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for (unsigned int ii = 0; ii < NUM_SHADERS; ii++)
	{
		glAttachShader(m_program, m_shaders[ii]);
	}

	glBindAttribLocation(m_program, 0, "position");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program linking failed");
}


Shader::~Shader()
{
	for (unsigned int ii = 0; ii < NUM_SHADERS; ii++)
	{
		glDetachShader(m_program, m_shaders[ii]);
		glDeleteShader(m_shaders[ii]);
	}

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::addUniform(std::string uniform)
{
	GLint uniformLocation = glGetUniformLocation(m_program, uniform.c_str());

	if (uniformLocation == 0xFFFFFFFF)
	{
		std::cerr << "Error: Could not find uniform " + uniform << std::endl;
		exit(1);
	}

	m_uniforms[uniform] = uniformLocation;
}

void Shader::setUniform(std::string uniformName, GLint value)
{
	glUniform1i(m_uniforms[uniformName], value);
}

void Shader::setUniform(std::string uniformName, GLfloat value)
{
	glUniform1f(m_uniforms[uniformName], value);
}

void Shader::setUniform(std::string uniformName, glm::vec3 value)
{
	glUniform3f(m_uniforms[uniformName], value.x, value.y, value.z);
}

void Shader::setUniform(std::string uniformName, glm::vec4 value)
{
	glUniform4f(m_uniforms[uniformName], value.x, value.y, value.z, value.w);
}

void Shader::setUniform(std::string uniformName, glm::mat4 value)
{
	glUniformMatrix4fv(m_uniforms[uniformName], 1, GL_FALSE, &value[0][0]);
}
