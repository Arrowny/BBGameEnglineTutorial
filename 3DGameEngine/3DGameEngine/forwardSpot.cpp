#include "forwardSpot.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardSpot::ForwardSpot(const std::string& fileName)
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

	m_uniforms[SPOTLBC_1] = glGetUniformLocation(m_program, "spotLight.pointLight.base.color");
	m_uniforms[SPOTLBI_1] = glGetUniformLocation(m_program, "spotLight.pointLight.base.intensity");
	m_uniforms[SPOTLAC_1] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.constant");
	m_uniforms[SPOTLAL_1] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.linear");
	m_uniforms[SPOTLAE_1] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.exponent");
	m_uniforms[SPOTLP_1] = glGetUniformLocation(m_program, "spotLight.pointLight.position");
	m_uniforms[SPOTLR_1] = glGetUniformLocation(m_program, "spotLight.pointLight.range");
	m_uniforms[SPOTLD_1] = glGetUniformLocation(m_program, "spotLight.direction");
	m_uniforms[SPOTLC_1] = glGetUniformLocation(m_program, "spotLight.cutoff");

}

void ForwardSpot::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{;
	glm::mat4 Normal = transform.GetModel();
	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetTransformedPos();
	glm::vec3 ambient = renderingEngine->GetAmbientLight();

	spotLight sLight = *(spotLight*)renderingEngine->GetActiveLight();

	glm::vec3 spotColor = sLight.m_color;
	glm::vec3 spotPos = sLight.GetTransform().GetTransformedPos();
	glm::vec3 spotDir = sLight.direction;

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);

	glUniform1f(m_uniforms[SPECI_U], (float)material.specularIntensity);
	glUniform1f(m_uniforms[SPECP_U], (float)material.specularPower);
	glUniform3fv(m_uniforms[EYEPOS_U], 1, &eyePos[0]);

	glUniform3fv(m_uniforms[SPOTLBC_1], 1, &spotColor[0]);
	glUniform3fv(m_uniforms[SPOTLP_1], 1, &spotPos[0]);
	glUniform3fv(m_uniforms[SPOTLD_1], 1, &spotDir[0]);

	glUniform1f(m_uniforms[SPOTLBI_1], (float)sLight.m_intensity);
	glUniform1f(m_uniforms[SPOTLAC_1], (float)sLight.atten.m_constant);
	glUniform1f(m_uniforms[SPOTLAE_1], (float)sLight.atten.m_exponent);
	glUniform1f(m_uniforms[SPOTLAL_1], (float)sLight.atten.m_linear);
	glUniform1f(m_uniforms[SPOTLR_1], (float)sLight.range);
	glUniform1f(m_uniforms[SPOTLC_1], (float)sLight.cutoff);

}

