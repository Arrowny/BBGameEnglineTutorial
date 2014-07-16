#include "forwardDirectional.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardDirectional::ForwardDirectional(const std::string& fileName)
{
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++){
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	CompileShader();

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[NORMAL_U] = glGetUniformLocation(m_program, "Normal");

	m_uniforms[SPECI_U] = glGetUniformLocation(m_program, "specularIntensity");
	m_uniforms[SPECP_U] = glGetUniformLocation(m_program, "specularPower");
	m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
	m_uniforms[DIRLIGHTC_U] = glGetUniformLocation(m_program, "directionalLight.base.color");
	m_uniforms[DIRLIGHTI_U] = glGetUniformLocation(m_program, "directionalLight.base.intensity");
	m_uniforms[DIRLIGHTD_U] = glGetUniformLocation(m_program, "directionalLight.direction");
	
}

void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 Normal = transform.GetModel();
	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetTransformedPos();
	material.GetTexture("diffuse")->Bind(0);

	directionalLight dirLight = *(directionalLight*)renderingEngine->GetActiveLight();

	glm::vec3 dirColor = dirLight.m_color;
	glm::vec3 dirDirection = dirLight.GetTransform().GetForward();;

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);

	glUniform1f(m_uniforms[SPECI_U], (float)material.GetFloat("specularIntensity"));
	glUniform1f(m_uniforms[SPECP_U], (float)material.GetFloat("specularPower"));
	glUniform3fv(m_uniforms[EYEPOS_U], 1, &eyePos[0]);
	glUniform3fv(m_uniforms[DIRLIGHTC_U], 1, &dirColor[0]);
	glUniform1f(m_uniforms[DIRLIGHTI_U], (float)dirLight.m_intensity);
	glUniform3fv(m_uniforms[DIRLIGHTD_U], 1, &dirDirection[0]);

}
