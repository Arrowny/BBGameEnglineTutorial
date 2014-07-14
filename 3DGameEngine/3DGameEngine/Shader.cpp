#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");    // because we are not using "attribute vec3 position;" in the vertex shader file
	glBindAttribLocation(m_program, 1, "texCoord");   
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Porgram linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

	m_uniforms[TRANSFORM_P_U] = glGetUniformLocation(m_program, "transformProjected");
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[BASIC_COLOR_U] = glGetUniformLocation(m_program, "basicColor");
	m_uniforms[L_AMBIENT_U] = glGetUniformLocation(m_program, "ambientLight");
	m_uniforms[L_DIRECTIONAL_BASE_COLOR_U] = glGetUniformLocation(m_program, "directionalLight.base.color");
	m_uniforms[L_DIRECTIONAL_BASE_INTENSITY_U] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
	m_uniforms[L_DIRECTIONAL_DIRECTION_U] = glGetUniformLocation(m_program, "directionalLight.direction");
	m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
	m_uniforms[L_SPECULARINTENSITY_U] = glGetUniformLocation(m_program, "specularIntensity");
	m_uniforms[L_SPECULARPOWER_U] = glGetUniformLocation(m_program, "specularPower");

	m_uniforms[L_POINT_BASE_COLOR_1U] = glGetUniformLocation(m_program, "pointLights[0].base.color");
	m_uniforms[L_POINT_BASE_INTENS_1U] = glGetUniformLocation(m_program, "pointLights[0].base.intensity");
	m_uniforms[L_POINT_ATTEN_CONS_1U] = glGetUniformLocation(m_program, "pointLights[0].atten.constant");
	m_uniforms[L_POINT_ATTEN_LINE_1U] = glGetUniformLocation(m_program, "pointLights[0].atten.linear");
	m_uniforms[L_POINT_ATTEN_EXPO_1U] = glGetUniformLocation(m_program, "pointLights[0].atten.exponent");
	m_uniforms[L_POINT_POSITION_1U] = glGetUniformLocation(m_program, "pointLights[0].position");
	m_uniforms[L_POINT_RANGE_1U] = glGetUniformLocation(m_program, "pointLights[0].range");

	m_uniforms[L_POINT_BASE_COLOR_2U] = glGetUniformLocation(m_program, "pointLights[1].base.color");
	m_uniforms[L_POINT_BASE_INTENS_2U] = glGetUniformLocation(m_program, "pointLights[1].base.intensity");
	m_uniforms[L_POINT_ATTEN_CONS_2U] = glGetUniformLocation(m_program, "pointLights[1].atten.constant");
	m_uniforms[L_POINT_ATTEN_LINE_2U] = glGetUniformLocation(m_program, "pointLights[1].atten.linear");
	m_uniforms[L_POINT_ATTEN_EXPO_2U] = glGetUniformLocation(m_program, "pointLights[1].atten.exponent");
	m_uniforms[L_POINT_POSITION_2U] = glGetUniformLocation(m_program, "pointLights[1].position");
	m_uniforms[L_POINT_RANGE_2U] = glGetUniformLocation(m_program, "pointLights[1].range");

	m_uniforms[L_SPOT_POINT_BASE_COLOR_1U] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.color");
	m_uniforms[L_SPOT_POINT_BASE_INTENS_1U] = glGetUniformLocation(m_program, "spotLights[0].pointLight.base.intensity");
	m_uniforms[L_SPOT_POINT_ATTEN_CONS_1U] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.constant");
	m_uniforms[L_SPOT_POINT_ATTEN_LINE_1U] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.linear");
	m_uniforms[L_SPOT_POINT_ATTEN_EXPO_1U] = glGetUniformLocation(m_program, "spotLights[0].pointLight.atten.exponent");
	m_uniforms[L_SPOT_POINT_POSITION_1U] = glGetUniformLocation(m_program, "spotLights[0].pointLight.position");
	m_uniforms[L_SPOT_POINT_RANGE_1U] = glGetUniformLocation(m_program, "spotLights[0].pointLight.range");
	m_uniforms[L_SPOT_DIRECTION_1U] = glGetUniformLocation(m_program, "spotLights[0].direction");
	m_uniforms[L_SPOT_CUTOFF_1U] = glGetUniformLocation(m_program, "spotLights[0].cutoff");

	//m_uniforms[L_SPOT_POINT_BASE_COLOR_2U] = glGetUniformLocation(m_program, "spotLights[1].pointLight.base.color");
	//m_uniforms[L_SPOT_POINT_BASE_INTENS_2U] = glGetUniformLocation(m_program, "spotLights[1].pointLight.base.intensity");
	//m_uniforms[L_SPOT_POINT_ATTEN_CONS_2U] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.constant");
	//m_uniforms[L_SPOT_POINT_ATTEN_LINE_2U] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.linear");
	//m_uniforms[L_SPOT_POINT_ATTEN_EXPO_2U] = glGetUniformLocation(m_program, "spotLights[1].pointLight.atten.exponent");
	//m_uniforms[L_SPOT_POINT_POSITION_2U] = glGetUniformLocation(m_program, "spotLights[1].pointLight.position");
	////m_uniforms[L_SPOT_POINT_RANGE_2U] = glGetUniformLocation(m_program, "spotLights[1].pointLight.range");
	//m_uniforms[L_SPOT_DIRECTION_2U] = glGetUniformLocation(m_program, "spotLights[1].direction");
	//m_uniforms[L_SPOT_CUTOFF_2U] = glGetUniformLocation(m_program, "spotLights[1].cutoff");


	//m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
	//m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
	//m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");

	//m_uniforms[FLOAT_U] = glGetUniformLocation(m_program, "uniformfloat");

	//DirectionalLight directionalLight = DirectionalLight(&BaseLight(glm::vec3(1, 1, 1), 0.0f), glm::vec3(0, 0, 0)); //DirectionalLight(&BaseLight(glm::fvec3(1, 1, 1), 0.2f), glm::fvec3(0.0f, 0.2f, -0.5f));

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

void Shader::Update(Transform& transform, Camera& camera, Material& material)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	//glm::mat4 model = camera.GetViewProjection()* camera.InitCamera(camera.GetForward(), camera.GetUp())* 
	//	camera.InitTranslation(-camera.GetPos().x, -camera.GetPos().y, -camera.GetPos().z) * transform.GetModel();

	//glm::mat4 model = transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_P_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &transform.GetModel()[0][0]);
	glUniform3fv(m_uniforms[BASIC_COLOR_U], 1, &material.basic_color[0]);//, (GLfloat)material.GetColor().y, (GLfloat)material.GetColor().z);
	glUniform3fv(m_uniforms[L_AMBIENT_U],1,&ambientLight[0]);
	glUniform3fv(m_uniforms[L_DIRECTIONAL_BASE_COLOR_U], 1, &directionalLight.base.color[0]);
	glUniform1f(m_uniforms[L_DIRECTIONAL_BASE_INTENSITY_U], directionalLight.base.intensity);
	glUniform3fv(m_uniforms[L_DIRECTIONAL_DIRECTION_U], 1, &directionalLight.direction[0]);
	glUniform3fv(m_uniforms[EYEPOS_U], 1, &camera.GetPos()[0]);
	glUniform1f(m_uniforms[L_SPECULARINTENSITY_U], material.specularIntensity);
	glUniform1f(m_uniforms[L_SPECULARPOWER_U], material.specularPower);

	glUniform3fv(m_uniforms[L_POINT_BASE_COLOR_1U],1, &pointLights[0].base.color[0]);
	glUniform1f(m_uniforms[L_POINT_BASE_INTENS_1U], pointLights[0].base.intensity);
	glUniform1f(m_uniforms[L_POINT_ATTEN_CONS_1U], pointLights[0].atten.constant);
	glUniform1f(m_uniforms[L_POINT_ATTEN_LINE_1U], pointLights[0].atten.linear);
	glUniform1f(m_uniforms[L_POINT_ATTEN_EXPO_1U], pointLights[0].atten.exponent);
	glUniform3fv(m_uniforms[L_POINT_POSITION_1U],1, &pointLights[0].position[0]);
	glUniform1f(m_uniforms[L_POINT_RANGE_1U], pointLights[0].range);

	glUniform3fv(m_uniforms[L_POINT_BASE_COLOR_2U],1, &pointLights[1].base.color[0]);
	glUniform1f(m_uniforms[L_POINT_BASE_INTENS_2U], pointLights[1].base.intensity);
	glUniform1f(m_uniforms[L_POINT_ATTEN_CONS_2U], pointLights[1].atten.constant);
	glUniform1f(m_uniforms[L_POINT_ATTEN_LINE_2U], pointLights[1].atten.linear);
	glUniform1f(m_uniforms[L_POINT_ATTEN_EXPO_2U], pointLights[1].atten.exponent);
	glUniform3fv(m_uniforms[L_POINT_POSITION_2U],1, &pointLights[1].position[0]);
	glUniform1f(m_uniforms[L_POINT_RANGE_2U], pointLights[1].range);

	glUniform3fv(m_uniforms[L_SPOT_POINT_BASE_COLOR_1U], 1, &spotLights[0].pointLight.base.color[0]);
	glUniform1f(m_uniforms[L_SPOT_POINT_BASE_INTENS_1U], spotLights[0].pointLight.base.intensity);
	glUniform1f(m_uniforms[L_SPOT_POINT_ATTEN_CONS_1U], spotLights[0].pointLight.atten.constant);
	glUniform1f(m_uniforms[L_SPOT_POINT_ATTEN_LINE_1U], spotLights[0].pointLight.atten.linear);
	glUniform1f(m_uniforms[L_SPOT_POINT_ATTEN_EXPO_1U], spotLights[0].pointLight.atten.exponent);
	glUniform3fv(m_uniforms[L_SPOT_POINT_POSITION_1U], 1, &spotLights[0].pointLight.position[0]);
	glUniform1f(m_uniforms[L_SPOT_POINT_RANGE_1U], spotLights[0].pointLight.range);
	glUniform3fv(m_uniforms[L_SPOT_DIRECTION_1U], 1,&spotLights[0].direction[0]);
	glUniform1f(m_uniforms[L_SPOT_CUTOFF_1U], spotLights[0].cutoff);


	//glUniform3fv(m_uniforms[L_POINT_BASE_COLOR_2U], 1, &spotLights[1].pointLight.base.color[0]);
	//glUniform1f(m_uniforms[L_POINT_BASE_INTENS_2U], spotLights[1].pointLight.base.intensity);
	//glUniform1f(m_uniforms[L_POINT_ATTEN_CONS_2U], spotLights[1].pointLight.atten.constant);
	//glUniform1f(m_uniforms[L_POINT_ATTEN_LINE_2U], spotLights[1].pointLight.atten.linear);
	//glUniform1f(m_uniforms[L_POINT_ATTEN_EXPO_2U], spotLights[1].pointLight.atten.exponent);
	//glUniform3fv(m_uniforms[L_POINT_POSITION_2U], 1, &spotLights[1].pointLight.position[0]);
	//glUniform1f(m_uniforms[L_POINT_RANGE_2U], pointLights[1].range);
	//glUniform3fv(m_uniforms[L_SPOT_DIRECTION_2U], 1, &spotLights[1].direction[0]);
	//glUniform1f(m_uniforms[L_SPOT_CUTOFF_2U], spotLights[1].cutoff);
}

//void Shader::Update(float value)
//{
//	glUniform1f(m_uniforms[FLOAT_U], value);
//}

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