#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

glm::fvec3 ambientLight(0.2f, 0.2f, 0.2f);
directionalLight Shader::m_directionalLight = directionalLight(baseLight(glm::fvec3(1, 1, 1), 0.2f), glm::fvec3(0.0f, 0.2f, -0.5f));
pointLight* Shader::m_pointLights = NULL;
int Shader::m_numPointLights = 0;


Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++){
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

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

	m_uniforms[POINTLBC_1] = glGetUniformLocation(m_program, "pointLights[0].base.color");
	m_uniforms[POINTLBI_1] = glGetUniformLocation(m_program, "pointLights[0].base.intensity");
	m_uniforms[POINTLAC_1] = glGetUniformLocation(m_program, "pointLights[0].atten.constant");
	m_uniforms[POINTLAL_1] = glGetUniformLocation(m_program, "pointLights[0].atten.linear");
	m_uniforms[POINTLAE_1] = glGetUniformLocation(m_program, "pointLights[0].atten.exponent");
	m_uniforms[POINTLP_1] = glGetUniformLocation(m_program, "pointLights[0].position");
	m_uniforms[POINTLBC_2] = glGetUniformLocation(m_program, "pointLights[1].base.color");
	m_uniforms[POINTLBI_2] = glGetUniformLocation(m_program, "pointLights[1].base.intensity");
	m_uniforms[POINTLAC_2] = glGetUniformLocation(m_program, "pointLights[1].atten.constant");
	m_uniforms[POINTLAL_2] = glGetUniformLocation(m_program, "pointLights[1].atten.linear");
	m_uniforms[POINTLAE_2] = glGetUniformLocation(m_program, "pointLights[1].atten.exponent");
	m_uniforms[POINTLP_2] = glGetUniformLocation(m_program, "pointLights[1].position");

	/*for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		std::ostringstream pointLightNameBuilder;
		pointLightNameBuilder << "pointLights[" << i << "]";
		std::string pointLightName = pointLightNameBuilder.str();

		std::string baseColor		= pointLightName + ".base.color";
		std::string baseIntensity	= pointLightName + ".base.intensity";
		std::string attenConstant	= pointLightName + ".atten.constant";
		std::string attenLinear		= pointLightName + ".atten.linear";
		std::string attenExponent	= pointLightName + ".atten.exponent";
		std::string position		= pointLightName + ".position";

		m_uniforms[POINTLBC_U] = glGetUniformLocation(m_program, baseColor.c_str());
		m_uniforms[POINTLBI_U] = glGetUniformLocation(m_program, baseIntensity.c_str());
		m_uniforms[POINTLAC_U] = glGetUniformLocation(m_program, attenConstant.c_str());
		m_uniforms[POINTLAL_U] = glGetUniformLocation(m_program, attenExponent.c_str());
		m_uniforms[POINTLAE_U] = glGetUniformLocation(m_program, attenLinear.c_str());
		m_uniforms[POINTLP_U] = glGetUniformLocation(m_program, position.c_str());
		
	}*/
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

float temp = 0.0f;

void Shader::Update(const Transform& transform, const Camera camera, const glm::fvec4 color, float specI, float specP)
{
	temp += Time::getDelta();
	glm::mat4 model = transform.GetProjection(camera);
	glm::mat4 Normal = transform.GetModel();
	glm::vec3 eyePos = transform.GetCameraPos(camera);

	glUniform1f(m_uniforms[UNIFORM_U], (float)glm::abs(glm::sin(temp)));
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(m_uniforms[LIGHTDIR_U], 0.0f, 1.0f, 1.0f);
	glUniform3f(m_uniforms[AMBIENTL_U], (float)ambientLight[0], (float)ambientLight[1], (float)ambientLight[2]);
	glUniform4f(m_uniforms[COLOR_U], (float)color[0], (float)color[1], (float)color[2], (float)color[3]);
	glUniform3f(m_uniforms[DIRLIGHTC_U], (float)m_directionalLight.m_base.m_color[0], (float)m_directionalLight.m_base.m_color[1], (float)m_directionalLight.m_base.m_color[2]);
	glUniform1f(m_uniforms[DIRLIGHTI_U], (float)m_directionalLight.m_base.m_intensity);
	glUniform3f(m_uniforms[DIRLIGHTD_U], (float)m_directionalLight.m_direction[0], (float)m_directionalLight.m_direction[1], (float)m_directionalLight.m_direction[2]);
	glUniform1f(m_uniforms[SPECI_U], (float)specI);
	glUniform1f(m_uniforms[SPECP_U], (float)specP);
	glUniform3f(m_uniforms[EYEPOS_U], (float)eyePos[0], (float)eyePos[1], (float)eyePos[2]);

	glUniform3f(m_uniforms[POINTLBC_1], (float)m_pointLights[0].base.m_color[0], (float)m_pointLights[0].base.m_color[1], (float)m_pointLights[0].base.m_color[2]);
	glUniform1f(m_uniforms[POINTLBI_1], (float)m_pointLights[0].base.m_intensity);
	glUniform1f(m_uniforms[POINTLAC_1], (float)m_pointLights[0].atten.m_constant);
	glUniform1f(m_uniforms[POINTLAE_1], (float)m_pointLights[0].atten.m_exponent);
	glUniform1f(m_uniforms[POINTLAL_1], (float)m_pointLights[0].atten.m_linear);
	glUniform3f(m_uniforms[POINTLP_1], (float)m_pointLights[0].position[0], (float)m_pointLights[0].position[1], (float)m_pointLights[0].position[2]);

	glUniform3f(m_uniforms[POINTLBC_2], (float)m_pointLights[1].base.m_color[0], (float)m_pointLights[1].base.m_color[1], (float)m_pointLights[1].base.m_color[2]);
	glUniform1f(m_uniforms[POINTLBI_2], (float)m_pointLights[1].base.m_intensity);
	glUniform1f(m_uniforms[POINTLAC_2], (float)m_pointLights[1].atten.m_constant);
	glUniform1f(m_uniforms[POINTLAE_2], (float)m_pointLights[1].atten.m_exponent);
	glUniform1f(m_uniforms[POINTLAL_2], (float)m_pointLights[1].atten.m_linear);
	glUniform3f(m_uniforms[POINTLP_2], (float)m_pointLights[1].position[0], (float)m_pointLights[1].position[1], (float)m_pointLights[1].position[2]);

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
			output.append(line + "\n");
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

void Shader::SetPointLights(pointLight* pointLights, int arraySize)
{
	if (arraySize > MAX_POINT_LIGHTS)
	{
		std::cerr << "Error: Too many point lights. Max allowed:" << MAX_POINT_LIGHTS << "Making:" << arraySize << std::endl;
	}
	else
	{
		Shader::m_numPointLights = arraySize;
		Shader::m_pointLights = pointLights;
		
	}
}
