#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include "Util.h"

Shader::Shader()
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}
}

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++){
		glAttachShader(m_program, m_shaders[i]);
	}

	CompileShader();

	m_uniforms[UNIFORM_U] = glGetUniformLocation(m_program, "uniformFloat");
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[NORMAL_U] = glGetUniformLocation(m_program, "Normal");
	m_uniforms[LIGHTDIR_U] = glGetUniformLocation(m_program, "lightDirection");
	m_uniforms[COLOR_U] = glGetUniformLocation(m_program, "baseColor");
	m_uniforms[AMBIENTL_U] = glGetUniformLocation(m_program, "ambientLight");
	m_uniforms[DIRLIGHTC_U] = glGetUniformLocation(m_program, "directionalLight.base.color");
	m_uniforms[DIRLIGHTI_U] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
	m_uniforms[DIRLIGHTD_U] = glGetUniformLocation(m_program, "directionalLight.direction");
	m_uniforms[SPECI_U] = glGetUniformLocation(m_program, "specularIntensity");
	m_uniforms[SPECP_U] = glGetUniformLocation(m_program, "specularPower");
	m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");

	m_uniforms[POINTLBC_U] = glGetUniformLocation(m_program, "pointLight.base.color");
	m_uniforms[POINTLBI_U] = glGetUniformLocation(m_program, "pointLight.base.intensity");
	m_uniforms[POINTLAC_U] = glGetUniformLocation(m_program, "pointLight.atten.constant");
	m_uniforms[POINTLAL_U] = glGetUniformLocation(m_program, "pointLight.atten.linear");
	m_uniforms[POINTLAE_U] = glGetUniformLocation(m_program, "pointLight.atten.exponent");
	m_uniforms[POINTLP_U] = glGetUniformLocation(m_program, "pointLight.position");
	m_uniforms[POINTLR_U] = glGetUniformLocation(m_program, "pointLight.range");

	m_uniforms[SPOTLBC_U] = glGetUniformLocation(m_program, "spotLight.pointLight.base.color");
	m_uniforms[SPOTLBI_U] = glGetUniformLocation(m_program, "spotLights.pointLight.base.intensity");
	m_uniforms[SPOTLAC_U] = glGetUniformLocation(m_program, "spotLights.pointLight.atten.constant");
	m_uniforms[SPOTLAL_U] = glGetUniformLocation(m_program, "spotLights.pointLight.atten.linear");
	m_uniforms[SPOTLAE_U] = glGetUniformLocation(m_program, "spotLights.pointLight.atten.exponent");
	m_uniforms[SPOTLP_U] = glGetUniformLocation(m_program, "spotLights.pointLight.position");
	m_uniforms[SPOTLR_U] = glGetUniformLocation(m_program, "spotLights.pointLight.range");
	m_uniforms[SPOTLD_U] = glGetUniformLocation(m_program, "spotLights.direction");
	m_uniforms[SPOTLC_U] = glGetUniformLocation(m_program, "spotLights.cutoff");

}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::CompileShader()
{
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");
}

float temp = 0.0f;

void Shader::Update(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	//temp += Time::getDelta();
	
	glm::mat4 Normal = transform.GetModel();
	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetTransformedPos();
	glm::vec3 ambient = renderingEngine->GetAmbientLight();
	material.GetTexture("diffuse")->Bind(0);

	directionalLight dirLight = *(directionalLight*)renderingEngine->GetActiveLight();
	spotLight sLight = *(spotLight*)renderingEngine->GetActiveLight();
	pointLight pLight = *(pointLight*)renderingEngine->GetActiveLight();

	glm::vec3 dirColor = dirLight.m_color;
	glm::vec3 dirDirection = dirLight.GetTransform().GetTransformedForward();
	glm::vec3 pointColor = pLight.m_color;
	glm::vec3 pointPos = pLight.GetTransform().GetTransformedPos();
	glm::vec3 spotColor = sLight.m_color;
	glm::vec3 spotPos = sLight.GetTransform().GetTransformedPos();
	glm::vec3 spotDir = sLight.GetTransform().GetTransformedForward();

	glUniform1f(m_uniforms[UNIFORM_U], (float)glm::abs(glm::sin(temp)));
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(m_uniforms[LIGHTDIR_U], 0.0f, 1.0f, 1.0f);
	glUniform3fv(m_uniforms[AMBIENTL_U], 1, &ambient[0]);
	glUniform4fv(m_uniforms[COLOR_U], 1, &material.color[0]);
	glUniform1f(m_uniforms[SPECI_U], (float)material.GetFloat("specularIntensity"));
	glUniform1f(m_uniforms[SPECP_U], (float)material.GetFloat("specularPower"));
	glUniform3fv(m_uniforms[EYEPOS_U], 1, &eyePos[0]);

	glUniform3fv(m_uniforms[DIRLIGHTC_U], 1, &dirColor[0]);
	glUniform1f(m_uniforms[DIRLIGHTI_U], (float)dirLight.m_intensity);
	glUniform3fv(m_uniforms[DIRLIGHTD_U], 1, &dirDirection[0]);

	glUniform3fv(m_uniforms[POINTLBC_U], 1, &pointColor[0]);
	glUniform3fv(m_uniforms[POINTLP_U], 1, &pointPos[0]);
	glUniform1f(m_uniforms[POINTLBI_U], (float)pLight.m_intensity);
	glUniform1f(m_uniforms[POINTLAC_U], (float)pLight.atten.m_constant);
	glUniform1f(m_uniforms[POINTLAE_U], (float)pLight.atten.m_exponent);
	glUniform1f(m_uniforms[POINTLAL_U], (float)pLight.atten.m_linear);
	glUniform1f(m_uniforms[POINTLR_U], (float)pLight.range);

	glUniform3fv(m_uniforms[SPOTLBC_U], 1, &spotColor[0]);
	glUniform3fv(m_uniforms[SPOTLP_U], 1, &spotPos[0]);
	glUniform3fv(m_uniforms[SPOTLD_U], 1, &spotDir[0]);
	glUniform1f(m_uniforms[SPOTLBI_U], (float)sLight.m_intensity);
	glUniform1f(m_uniforms[SPOTLAC_U], (float)sLight.atten.m_constant);
	glUniform1f(m_uniforms[SPOTLAE_U], (float)sLight.atten.m_exponent);
	glUniform1f(m_uniforms[SPOTLAL_U], (float)sLight.atten.m_linear);
	glUniform1f(m_uniforms[SPOTLR_U], (float)sLight.range);
	glUniform1f(m_uniforms[SPOTLC_U], (float)sLight.cutoff);

}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			if (line.find("#include") == std::string::npos)
			{
				output.append(line + "\n");
			}
			else
			{
				std::string includeFileName = Util::Split(line, ' ')[1];
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

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
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

			glBindAttribLocation(m_program, currentAttribLocation, attributeName.c_str());
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

			//AddUniform(uniformName, uniformType, structs);
		}
		uniformLocation = shaderText.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
	}
}