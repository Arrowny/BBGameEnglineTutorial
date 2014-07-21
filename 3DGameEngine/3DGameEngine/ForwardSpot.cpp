#include "ForwardSpot.h"


ForwardSpot::ForwardSpot(const std::string& fileName)
{
	fprintf(stderr, "in point shader \n");
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

	m_uniforms[L_SPOT_POINT_BASE_COLOR] = glGetUniformLocation(m_program, "spotLight.pointLight.base.color");
	m_uniforms[L_SPOT_POINT_BASE_INTENS] = glGetUniformLocation(m_program, "spotLight.pointLight.base.intensity");
	m_uniforms[L_SPOT_POINT_ATTEN_CONS] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.constant");
	m_uniforms[L_SPOT_POINT_ATTEN_LINE] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.linear");
	m_uniforms[L_SPOT_POINT_ATTEN_EXPO] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.exponent");
	m_uniforms[L_SPOT_POINT_POSITION] = glGetUniformLocation(m_program, "spotLight.pointLight.position");
	m_uniforms[L_SPOT_POINT_RANGE] = glGetUniformLocation(m_program, "spotLight.pointLight.range");
	m_uniforms[L_SPOT_DIRECTION] = glGetUniformLocation(m_program, "spotLight.direction");
	m_uniforms[L_SPOT_CUTOFF] = glGetUniformLocation(m_program, "spotLight.cutoff");
}


ForwardSpot::~ForwardSpot()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}



void ForwardSpot::Update(Transform& transform, RenderingEngine& renderingEngine, Material& material)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine.GetMainCamera().GetViewProjection()* worldMatrix;
	//glm::mat4 projectedMatrix =GetRenderingEngine()->GetMainCamera().GetViewProjection()* worldMatrix; // can not use GetRenderingEngine()->.........do not know why......
	//glm::mat4 model = projectedMatrix * worldMatrix;

	glUniformMatrix4fv(m_uniforms[model], 1, GL_FALSE, &worldMatrix[0][0]);
	glUniformMatrix4fv(m_uniforms[MVP], 1, GL_FALSE, &projectedMatrix[0][0]);
	glUniform3fv(m_uniforms[EYEPOS_U], 1, &renderingEngine.GetMainCamera().GetTransform().GetPos()[0]);
	glUniform1f(m_uniforms[L_SPECULARINTENSITY_U], material.specularIntensity);
	glUniform1f(m_uniforms[L_SPECULARPOWER_U], material.specularPower);

	SpotLight spotLight = *(SpotLight*)renderingEngine.GetActiveLight();

	glUniform3fv(m_uniforms[L_SPOT_POINT_BASE_COLOR], 1, &spotLight.color[0]);
	glUniform1f(m_uniforms[L_SPOT_POINT_BASE_INTENS], spotLight.intensity);
	glUniform1f(m_uniforms[L_SPOT_POINT_ATTEN_CONS], spotLight.atten.constant);
	glUniform1f(m_uniforms[L_SPOT_POINT_ATTEN_LINE], spotLight.atten.linear);
	glUniform1f(m_uniforms[L_SPOT_POINT_ATTEN_EXPO], spotLight.atten.exponent);
	glUniform3fv(m_uniforms[L_SPOT_POINT_POSITION], 1, &spotLight.GetTransform().GetPos()[0]);
	glUniform1f(m_uniforms[L_SPOT_POINT_RANGE], spotLight.range);
	glUniform3fv(m_uniforms[L_SPOT_DIRECTION], 1, &spotLight.GetDirection()[0]);
	glUniform1f(m_uniforms[L_SPOT_CUTOFF], spotLight.cutoff);


 }