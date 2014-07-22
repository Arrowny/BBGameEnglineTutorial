#include "ForwardDirectional.h"


ForwardDirectional::ForwardDirectional(const std::string& fileName)
{
	fprintf(stderr, "in DIRECTIONAL shader \n");
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Porgram linking failed");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");



	m_uniforms[MVP] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[model] = glGetUniformLocation(m_program, "model");

	m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
	m_uniforms[L_SPECULARINTENSITY_U] = glGetUniformLocation(m_program, "specularIntensity");
	m_uniforms[L_SPECULARPOWER_U] = glGetUniformLocation(m_program, "specularPower");

	m_uniforms[L_DIRECTIONAL_BASE_COLOR_U] = glGetUniformLocation(m_program, "directionalLight.base.color");
	m_uniforms[L_DIRECTIONAL_BASE_INTENSITY_U] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
	m_uniforms[L_DIRECTIONAL_DIRECTION_U] = glGetUniformLocation(m_program, "directionalLight.direction");


}


ForwardDirectional::~ForwardDirectional()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}



void ForwardDirectional::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;

	glUniformMatrix4fv(m_uniforms[model], 1, GL_FALSE, &worldMatrix[0][0]);
	glUniformMatrix4fv(m_uniforms[MVP], 1, GL_FALSE, &projectedMatrix[0][0]);

	glUniform3fv(m_uniforms[EYEPOS_U], 1, &renderingEngine.GetMainCamera().GetTransform().GetTransformedPos()[0]);
	glUniform1f(m_uniforms[L_SPECULARINTENSITY_U], material.GetFloat("specularIntensity"));
	glUniform1f(m_uniforms[L_SPECULARPOWER_U], material.GetFloat("specularPower"));

	DirectionalLight directionalLight = *(DirectionalLight*)renderingEngine.GetActiveLight();  // if activeLight in the renderingEngine is not a pointer, then this code doesnot work

	glUniform3fv(m_uniforms[L_DIRECTIONAL_BASE_COLOR_U], 1, &directionalLight.color[0]);
	glUniform1f(m_uniforms[L_DIRECTIONAL_BASE_INTENSITY_U], directionalLight.intensity);
	glUniform3fv(m_uniforms[L_DIRECTIONAL_DIRECTION_U], 1, &directionalLight.GetDirection()[0]);




}