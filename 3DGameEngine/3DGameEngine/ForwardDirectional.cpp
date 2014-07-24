#include "ForwardDirectional.h"


ForwardDirectional::ForwardDirectional() :Shader("./res/shader/fowardDirectional")
{


	//m_uniforms[MVP] = glGetUniformLocation(m_program, "MVP");
	//m_uniforms[model] = glGetUniformLocation(m_program, "model");

	//m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
	//m_uniforms[L_SPECULARINTENSITY_U] = glGetUniformLocation(m_program, "specularIntensity");
	//m_uniforms[L_SPECULARPOWER_U] = glGetUniformLocation(m_program, "specularPower");

	//m_uniforms[L_DIRECTIONAL_BASE_COLOR_U] = glGetUniformLocation(m_program, "directionalLight.base.color");
	//m_uniforms[L_DIRECTIONAL_BASE_INTENSITY_U] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
	//m_uniforms[L_DIRECTIONAL_DIRECTION_U] = glGetUniformLocation(m_program, "directionalLight.direction");

	AddUniform("T_model");
	AddUniform("T_MVP");
	AddUniform("C_eyePos");
	AddUniform("specularIntensity");
	AddUniform("specularPower");

	AddUniform("R_directionalLight.base.color");
	AddUniform("R_directionalLight.base.intensity");
	AddUniform("R_directionalLight.direction");
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

	SetUniform("T_model",worldMatrix);
	SetUniform("T_MVP",projectedMatrix);

	SetUniform("C_eyePos", renderingEngine.GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	DirectionalLight directionalLight = *(DirectionalLight*)renderingEngine.GetActiveLight();  // if activeLight in the renderingEngine is not a pointer, then this code doesnot work

	SetUniform("R_directionalLight.base.color", directionalLight.color);
	SetUniformf("R_directionalLight.base.intensity", directionalLight.intensity);
	SetUniform("R_directionalLight.direction", directionalLight.GetDirection());




}