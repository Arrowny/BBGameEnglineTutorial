#include "Shader.h"
#include "Util.h"
#include <fstream>
#include <iostream>
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

Shader::Shader(std::string& fileName)
{
	std::string vertexShaderText = LoadShader(fileName + ".vs");
	std::string fragmentShaderText = LoadShader(fileName + ".fs");

	m_shaders[0] = CreateShader(vertexShaderText, GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(fragmentShaderText, GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Porgram linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");
}

Shader::~Shader()
{
}

void Shader::Bind()
{
	glUseProgram(m_program);
}


GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "error: shader creation failed!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str(); // conver a regular string to a list of c chars
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed");

	return shader;
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

//static std::vector<UniformStruct> FindUniformStructs(const std::string& shaderText)
//{
//	static const std::string STRUCT_KEY = "struct";
//	std::vector<UniformStruct> result;
//
//	size_t structLocation = shaderText.find(STRUCT_KEY);
//	while (structLocation != std::string::npos)
//	{
//		structLocation += STRUCT_KEY.length() + 1; //Ignore the struct keyword and space
//
//		size_t braceOpening = shaderText.find("{", structLocation);
//		size_t braceClosing = shaderText.find("}", braceOpening);
//
//		UniformStruct newStruct;
//		newStruct.name = FindUniformStructName(shaderText.substr(structLocation, braceOpening - structLocation));
//		newStruct.memberNames = FindUniformStructComponents(shaderText.substr(braceOpening, braceClosing - braceOpening));
//
//		result.push_back(newStruct);
//		structLocation = shaderText.find(STRUCT_KEY, structLocation);
//	}
//
//	return result;
//}
//
//void Shader::AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs)
//{
//	bool addThis = true;
//
//	for (unsigned int i = 0; i < structs.size(); i++)
//	{
//		if (structs[i].name.compare(uniformType) == 0)
//		{
//			addThis = false;
//			for (unsigned int j = 0; j < structs[i].memberNames.size(); j++)
//			{
//				AddUniform(uniformName + "." + structs[i].memberNames[j].name, structs[i].memberNames[j].type, structs);
//			}
//		}
//	}
//
//	if (!addThis)
//		return;
//
//	unsigned int location = glGetUniformLocation(m_program, uniformName.c_str());
//
//	assert(location != INVALID_VALUE);
//
//	m_uniforms.insert(std::pair<std::string, UniformData>(uniformName, UniformData(location, uniformType)));
//	//result.push_back(UniformData(location, uniformType, uniformName));
//}
//
//void Shader::AddShaderUniforms(const std::string& shaderText)
//{
//	static const std::string UNIFORM_KEY = "uniform";
//
//	//std::vector<UniformStruct> structs = FindUniformStructs(shaderText);
//
//	size_t uniformLocation = shaderText.find(UNIFORM_KEY);
//	while (uniformLocation != std::string::npos)
//	{
//		bool isCommented = false;
//		size_t lastLineEnd = shaderText.rfind(";", uniformLocation);
//
//		if (lastLineEnd != std::string::npos)
//		{
//			std::string potentialCommentSection = shaderText.substr(lastLineEnd, uniformLocation - lastLineEnd);
//			isCommented = potentialCommentSection.find("//") != std::string::npos;
//		}
//
//		if (!isCommented)
//		{
//			size_t begin = uniformLocation + UNIFORM_KEY.length();
//			size_t end = shaderText.find(";", begin);
//
//			std::string uniformLine = shaderText.substr(begin + 1, end - begin - 1);
//
//			begin = uniformLine.find(" ");
//			std::string uniformName = uniformLine.substr(begin + 1);
//			std::string uniformType = uniformLine.substr(0, begin);
//
//			AddUniform(uniformName, uniformType, structs);
//		}
//		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
//	}
//}