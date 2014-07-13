#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

pointLight* Shader::m_pointLights = NULL;
spotLight* Shader::m_spotLights = NULL;
int Shader::m_numPointLights = 0;
int Shader::m_numSpotLights = 0;

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

	m_uniforms[POINTLBC_1] = glGetUniformLocation(m_program, "pointLights[0].base.color");
	m_uniforms[POINTLBI_1] = glGetUniformLocation(m_program, "pointLights[0].base.intensity");
	m_uniforms[POINTLAC_1] = glGetUniformLocation(m_program, "pointLights[0].atten.constant");
	m_uniforms[POINTLAL_1] = glGetUniformLocation(m_program, "pointLights[0].atten.linear");
	m_uniforms[POINTLAE_1] = glGetUniformLocation(m_program, "pointLights[0].atten.exponent");
	m_uniforms[POINTLP_1] = glGetUniformLocation(m_program, "pointLights[0].position");
	m_uniforms[POINTLR_1] = glGetUniformLocation(m_program, "pointLights[0].range");

	m_uniforms[POINTLBC_2] = glGetUniformLocation(m_program, "pointLights[1].base.color");
	m_uniforms[POINTLBI_2] = glGetUniformLocation(m_program, "pointLights[1].base.intensity");
	m_uniforms[POINTLAC_2] = glGetUniformLocation(m_program, "pointLights[1].atten.constant");
	m_uniforms[POINTLAL_2] = glGetUniformLocation(m_program, "pointLights[1].atten.linear");
	m_uniforms[POINTLAE_2] = glGetUniformLocation(m_program, "pointLights[1].atten.exponent");
	m_uniforms[POINTLP_2] = glGetUniformLocation(m_program, "pointLights[1].position");
	m_uniforms[POINTLR_2] = glGetUniformLocation(m_program, "pointLights[1].range");

	m_uniforms[SPOTLBC_1] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.color");
	m_uniforms[SPOTLBI_1] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.intensity");
	m_uniforms[SPOTLAC_1] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.constant");
	m_uniforms[SPOTLAL_1] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.linear");
	m_uniforms[SPOTLAE_1] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.exponent");
	m_uniforms[SPOTLP_1] = glGetUniformLocation(m_program, "spotLights[0].pointLight.position");
	m_uniforms[SPOTLR_1] = glGetUniformLocation(m_program, "spotLights[0].pointLight.range");
	m_uniforms[SPOTLD_1] = glGetUniformLocation(m_program, "spotLights[0].direction");
	m_uniforms[SPOTLC_1] = glGetUniformLocation(m_program, "spotLights[0].cutoff");

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
	glm::mat4 model = transform.GetProjection(renderingEngine->GetMainCamera());
	glm::mat4 Normal = transform.GetModel();
	glm::vec3 eyePos = transform.GetCameraPos(renderingEngine->GetMainCamera());
	glm::vec3 ambient = renderingEngine->GetAmbientLight();
	glm::vec3 dirColor = renderingEngine->GetDirectionalLight().m_base.m_color;
	glm::vec3 dirDirection = renderingEngine->GetDirectionalLight().m_direction;
	glm::vec3 pointColor = renderingEngine->GetPointLight().base.m_color;
	glm::vec3 pointPos = renderingEngine->GetPointLight().position;
	glm::vec3 spotColor = renderingEngine->GetSpotLight().pointL.base.m_color;
	glm::vec3 spotPos = renderingEngine->GetSpotLight().pointL.position;
	glm::vec3 spotDir = renderingEngine->GetSpotLight().direction;

	glUniform1f(m_uniforms[UNIFORM_U], (float)glm::abs(glm::sin(temp)));
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(m_uniforms[LIGHTDIR_U], 0.0f, 1.0f, 1.0f);
	glUniform3f(m_uniforms[AMBIENTL_U], (float)renderingEngine->GetAmbientLight()[0], (float)renderingEngine->GetAmbientLight()[1], (float)renderingEngine->GetAmbientLight()[2]);
	glUniform4fv(m_uniforms[COLOR_U], 1, &material.color[0]);
	glUniform3fv(m_uniforms[DIRLIGHTC_U], 1, &dirColor[0]);
	glUniform1f(m_uniforms[DIRLIGHTI_U], (float)renderingEngine->GetDirectionalLight().m_base.m_intensity);
	glUniform3fv(m_uniforms[DIRLIGHTD_U], 1, &dirDirection[0]);
	glUniform1f(m_uniforms[SPECI_U], (float)material.specularIntensity);
	glUniform1f(m_uniforms[SPECP_U], (float)material.specularPower);
	glUniform3fv(m_uniforms[EYEPOS_U], 1, &eyePos[0]);

	glUniform3fv(m_uniforms[POINTLBC_1], 1, &pointColor[0]);
	glUniform1f(m_uniforms[POINTLBI_1], (float)renderingEngine->GetPointLight().base.m_intensity);
	glUniform1f(m_uniforms[POINTLAC_1], (float)renderingEngine->GetPointLight().atten.m_constant);
	glUniform1f(m_uniforms[POINTLAE_1], (float)renderingEngine->GetPointLight().atten.m_exponent);
	glUniform1f(m_uniforms[POINTLAL_1], (float)renderingEngine->GetPointLight().atten.m_linear);
	glUniform3fv(m_uniforms[POINTLP_1], 1, &pointPos[0]);
	glUniform1f(m_uniforms[POINTLR_1], (float)renderingEngine->GetPointLight().range);

	glUniform3f(m_uniforms[POINTLBC_2], (float)m_pointLights[1].base.m_color[0], (float)m_pointLights[1].base.m_color[1], (float)m_pointLights[1].base.m_color[2]);
	glUniform1f(m_uniforms[POINTLBI_2], (float)m_pointLights[1].base.m_intensity);
	glUniform1f(m_uniforms[POINTLAC_2], (float)m_pointLights[1].atten.m_constant);
	glUniform1f(m_uniforms[POINTLAE_2], (float)m_pointLights[1].atten.m_exponent);
	glUniform1f(m_uniforms[POINTLAL_2], (float)m_pointLights[1].atten.m_linear);
	glUniform3f(m_uniforms[POINTLP_2], (float)m_pointLights[1].position[0], (float)m_pointLights[1].position[1], (float)m_pointLights[1].position[2]);
	glUniform1f(m_uniforms[POINTLR_2], (float)m_pointLights[1].range);

	glUniform3fv(m_uniforms[SPOTLBC_1], 1, &spotColor[0]);
	glUniform1f(m_uniforms[SPOTLBI_1], (float)renderingEngine->GetSpotLight().pointL.base.m_intensity);
	glUniform1f(m_uniforms[SPOTLAC_1], (float)renderingEngine->GetSpotLight().pointL.atten.m_constant);
	glUniform1f(m_uniforms[SPOTLAE_1], (float)renderingEngine->GetSpotLight().pointL.atten.m_exponent);
	glUniform1f(m_uniforms[SPOTLAL_1], (float)renderingEngine->GetSpotLight().pointL.atten.m_linear);
	glUniform3fv(m_uniforms[SPOTLP_1], 1, &spotPos[0]);
	glUniform1f(m_uniforms[SPOTLR_1], (float)renderingEngine->GetSpotLight().pointL.range);
	glUniform3fv(m_uniforms[SPOTLD_1], 1, &spotDir[0]);
	glUniform1f(m_uniforms[SPOTLC_1], (float)renderingEngine->GetSpotLight().cutoff);

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

void Shader::SetSpotLights(spotLight* spotLights, int arraySize)
{
	if (arraySize > MAX_SPOT_LIGHTS)
	{
		std::cerr << "Error: Too many spot lights" << std::endl;
	}
	else
	{
		Shader::m_numSpotLights = arraySize;
		Shader::m_spotLights = spotLights;
	}
}
