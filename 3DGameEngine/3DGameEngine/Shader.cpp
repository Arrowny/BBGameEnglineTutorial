#include "Shader.h"
#include "Util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <GL/glew.h>
#include <cstdlib>
//Class RenderdingEnginge;

Shader::Shader()
{
	m_program = glCreateProgram();
	if (m_program == 0)
	{
		fprintf(stderr, "m_program is not created\n");
		exit(1);
	}

	glBindAttribLocation(m_program, 0, "position");    // because we are not using "attribute vec3 position;" in the vertex shader file
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	
}

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	std::string vertexShaderText = LoadShader(fileName + ".vs");
	std::string fragmentShaderText = LoadShader(fileName + ".fs");

	AddVertexShader(vertexShaderText);
	AddFragmentShader(fragmentShaderText);

	AddAllAttributes(vertexShaderText);

	CompileShader();

	AddShaderUniforms(vertexShaderText);
	AddShaderUniforms(fragmentShaderText);
}

Shader::~Shader()
{
}

void Shader::CompileShader()
{
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
}


void Shader::AddVertexShaderFromFile(const std::string& text)
{
	AddVertexShader(LoadShader(text));
}

void Shader::AddGeometryShaderFromFile(const std::string& text)
{
	AddGeometryShader(LoadShader(text));
}

void Shader::AddFragmentShaderFromFile(const std::string& text)
{
	AddFragmentShader(LoadShader(text));
}

void Shader::AddVertexShader(const std::string& text)
{
	AddProgram(text, GL_VERTEX_SHADER);
}

void Shader::AddGeometryShader(const std::string& text)
{
	AddProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::AddFragmentShader(const std::string& text)
{
	AddProgram(text, GL_FRAGMENT_SHADER);
}
void Shader::Bind()
{
	glUseProgram(m_program);
}


//GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
//{
//	GLuint shader = glCreateShader(shaderType);
//
//	if (shader == 0)
//		std::cerr << "error: shader creation failed!" << std::endl;
//
//	const GLchar* shaderSourceStrings[1];
//	GLint shaderSourceStringLengths[1];
//
//	shaderSourceStrings[0] = text.c_str(); // conver a regular string to a list of c chars
//	shaderSourceStringLengths[0] = text.length();
//
//	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
//	glCompileShader(shader);
//	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed");
//
//	return shader;
//}
//
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

//	const std::string INCLUDE_DIRECTIVE = "#include";

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			if (line.find("#include") == std::string::npos)
				output.append(line + "\n");
			else
			{
				std::string includeFileName = Util::Split(line
					, ' ')[1];
				includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

				std::string toAppend = LoadShader(includeFileName);
				output.append(toAppend + "\n");
			}
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::AddProgram(const std::string& text, int type)
{
	int shader = glCreateShader(type);

	if (shader == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", type);
		exit(1);
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];

		glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader, InfoLog);

		exit(1);
	}

	glAttachShader(m_program, shader);
	m_shaders.push_back(shader);
}


void Shader::UpdateUniforms(Transform& transform, Material& material, RenderingEngine* renderingEngine)
{

}
void Shader::AddUniform(const std::string& uniform)
{
	unsigned int location = glGetUniformLocation(m_program, uniform.c_str());

	//assert(location != INVALID_VALUE);

	m_uniforms[uniform] = location;
}

void Shader::SetUniformi(const std::string& name, int value)
{
	glUniform1i(m_uniforms[name], value);
}

void Shader::SetUniformf(const std::string& name, float value)
{
	glUniform1f(m_uniforms[name], value);
}

void Shader::SetUniform(const std::string& name, const glm::fvec3& value)
{
	glUniform3f(m_uniforms[name], value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, &(value[0][0]));
}

void Shader::SetAttribLocation(const std::string& attributeName, int location)
{
	glBindAttribLocation(m_program, location, attributeName.c_str());
}

void Shader::AddAllAttributes(const std::string& vertexShaderText)
{
	static const std::string ATTRIBUTE_KEY = "attribute";

	int currentAttribLocation = 0;
	size_t attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY);
	while (attributeLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = vertexShaderText.rfind(";", attributeLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = vertexShaderText.substr(lastLineEnd, attributeLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = attributeLocation + ATTRIBUTE_KEY.length();
			size_t end = vertexShaderText.find(";", begin);

			std::string attributeLine = vertexShaderText.substr(begin + 1, end - begin - 1);

			begin = attributeLine.find(" ");
			std::string attributeName = attributeLine.substr(begin + 1);

			SetAttribLocation(attributeName, currentAttribLocation);
			currentAttribLocation++;
		}
		attributeLocation = vertexShaderText.find(ATTRIBUTE_KEY, attributeLocation + ATTRIBUTE_KEY.length());
	}
}

void Shader::AddShaderUniforms(const std::string& shaderText)
{
	static const std::string UNIFORM_KEY = "uniform";

	//std::vector<UniformStruct> structs = FindUniformStructs(shaderText);

	size_t uniformLocation = shaderText.find(UNIFORM_KEY);
	while (uniformLocation != std::string::npos)
	{
		bool isCommented = false;
		size_t lastLineEnd = shaderText.rfind(";", uniformLocation);

		if (lastLineEnd != std::string::npos)
		{
			std::string potentialCommentSection = shaderText.substr(lastLineEnd, uniformLocation - lastLineEnd);
			isCommented = potentialCommentSection.find("//") != std::string::npos;
		}

		if (!isCommented)
		{
			size_t begin = uniformLocation + UNIFORM_KEY.length();
			size_t end = shaderText.find(";", begin);

			std::string uniformLine = shaderText.substr(begin + 1, end - begin - 1);

			begin = uniformLine.find(" ");
			std::string uniformName = uniformLine.substr(begin + 1);
			std::string uniformType = uniformLine.substr(0, begin);

			if (uniformName != "diffuse")
			{
				AddUniform(uniformName);
			}

		}
		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}