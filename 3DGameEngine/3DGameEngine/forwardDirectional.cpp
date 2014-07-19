#include "forwardDirectional.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardDirectional::ForwardDirectional()
{
	AddVertexShaderFromFile("./res/forwardDirectional.vs");
	AddFragmentShaderFromFile("./res/forwardDirectional.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	CompileShader();

	AddUniform("transform");
	AddUniform("Normal");
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");
}

void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("Normal", worldMatrix);
	SetUniform("transform", projectedMatrix);

	SetUniform("eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	directionalLight dirLight = *(directionalLight*)renderingEngine->GetActiveLight();

	SetUniform("directionalLight.direction", dirLight.GetTransform().GetTransformedForward());
	SetUniform("directionalLight.base.color", dirLight.m_color);
	SetUniformf("directionalLight.base.intensity", dirLight.m_intensity);
}

//ForwardDirectional::ForwardDirectional(const std::string& fileName)
//{
//	std::string vertexShaderText = LoadShader(fileName + ".vs");
//	std::string fragmentShaderText = LoadShader(fileName + ".fs");
//
//	m_shaders[0] = CreateShader(vertexShaderText, GL_VERTEX_SHADER);
//	m_shaders[1] = CreateShader(fragmentShaderText, GL_FRAGMENT_SHADER);
//
//	for (unsigned int i = 0; i < NUM_SHADERS; i++){
//		glAttachShader(m_program, m_shaders[i]);
//	}
//
//	AddAllAttributes(vertexShaderText);
//	
//	CompileShader();
//
//	/*AddUniform("transform");
//	AddUniform("Normal");
//	AddUniform("specularIntensity");
//	AddUniform("specularPower");
//	AddUniform("eyePos");
//	AddUniform("directionalLight.base.color");
//	AddUniform("directionalLight.base.intensity");
//	AddUniform("directionalLight.direction");*/
//
//	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
//	m_uniforms[NORMAL_U] = glGetUniformLocation(m_program, "Normal");
//
//	m_uniforms[SPECI_U] = glGetUniformLocation(m_program, "specularIntensity");
//	m_uniforms[SPECP_U] = glGetUniformLocation(m_program, "specularPower");
//	m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
//	m_uniforms[DIRLIGHTC_U] = glGetUniformLocation(m_program, "directionalLight.base.color");
//	m_uniforms[DIRLIGHTI_U] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
//	m_uniforms[DIRLIGHTD_U] = glGetUniformLocation(m_program, "directionalLight.direction");
//	
//}
//
//void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
//{
//	glm::mat4 Normal = transform.GetModel();
//	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
//	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetTransformedPos();
//	material.GetTexture("diffuse")->Bind(0);
//
//	directionalLight dirLight = *(directionalLight*)renderingEngine->GetActiveLight();
//
//	glm::vec3 dirColor = dirLight.m_color;
//	glm::vec3 dirDirection = dirLight.GetTransform().GetTransformedForward();
//
//	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
//	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);
//
//	glUniform1f(m_uniforms[SPECI_U], (float)material.GetFloat("specularIntensity"));
//	glUniform1f(m_uniforms[SPECP_U], (float)material.GetFloat("specularPower"));
//	glUniform3fv(m_uniforms[EYEPOS_U], 1, &eyePos[0]);
//	glUniform3fv(m_uniforms[DIRLIGHTC_U], 1, &dirColor[0]);
//	glUniform1f(m_uniforms[DIRLIGHTI_U], (float)dirLight.m_intensity);
//	glUniform3fv(m_uniforms[DIRLIGHTD_U], 1, &dirDirection[0]);
//
//}
