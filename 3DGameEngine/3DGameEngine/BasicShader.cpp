#include "BasicShader.h"


BasicShader::BasicShader(const std::string& fileName)
{
	fprintf(stderr, "in basic shader \n");
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Porgram linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

	glBindAttribLocation(m_program, 0, "position");    // because we are not using "attribute vec3 position;" in the vertex shader file
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	m_uniforms[TRANSFORM_P_U] = glGetUniformLocation(m_program, "transformProjected");
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}


BasicShader::~BasicShader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}



void BasicShader::Update(Transform& transform, Camera& camera, Material& material)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = camera.GetViewProjection()* worldMatrix;
	//glm::mat4 model = projectedMatrix * worldMatrix;

	glUniformMatrix4fv(m_uniforms[TRANSFORM_P_U], 1, GL_FALSE, &projectedMatrix[0][0]);
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &worldMatrix[0][0]);

}