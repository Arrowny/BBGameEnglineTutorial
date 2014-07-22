#include "ForwardAmbient.h"


ForwardAmbient::ForwardAmbient(const std::string& fileName)
{
	fprintf(stderr, "in ambient shader \n");
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Porgram linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

	m_uniforms[MVP] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[ambientIntensity] = glGetUniformLocation(m_program, "ambientIntensity");
}


ForwardAmbient::~ForwardAmbient()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}



void ForwardAmbient::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;

	glUniformMatrix4fv(m_uniforms[MVP], 1, GL_FALSE, &projectedMatrix[0][0]);
	glUniform3fv(m_uniforms[ambientIntensity], 1, &renderingEngine.GetAmbientLight()[0]);

}