#include "forwardSpot.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardSpot::ForwardSpot()
{
	AddVertexShaderFromFile("./res/forwardSpot.vs");
	AddFragmentShaderFromFile("./res/forwardSpot.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);

	CompileShader();

	AddUniform("transform");
	AddUniform("Normal");
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
	AddUniform("spotLight.pointLight.base.color");
	AddUniform("spotLight.pointLight.base.intensity");
	AddUniform("spotLight.pointLight.atten.constant");
	AddUniform("spotLight.pointLight.atten.linear");
	AddUniform("spotLight.pointLight.atten.exponent");
	AddUniform("spotLight.pointLight.position");
	AddUniform("spotLight.pointLight.range");
	AddUniform("spotLight.direction");
	AddUniform("spotLight.cutoff");
}

void ForwardSpot::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("Normal", worldMatrix);
	SetUniform("transform", projectedMatrix);

	SetUniform("eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	spotLight sLight = *(spotLight*)renderingEngine->GetActiveLight();

	SetUniform("spotLight.pointLight.base.color", sLight.m_color);
	SetUniformf("spotLight.pointLight.base.intensity", sLight.m_intensity);
	SetUniformf("spotLight.pointLight.atten.constant", sLight.atten.m_constant);
	SetUniformf("spotLight.pointLight.atten.linear", sLight.atten.m_linear);
	SetUniformf("spotLight.pointLight.atten.exponent", sLight.atten.m_exponent);
	SetUniform("spotLight.pointLight.position", sLight.GetTransform().GetTransformedPos());
	SetUniformf("spotLight.pointLight.range", sLight.range);
	SetUniform("spotLight.direction", sLight.GetTransform().GetTransformedForward());
	SetUniformf("spotLight.cutoff", sLight.cutoff);
}
//ForwardSpot::ForwardSpot(const std::string& fileName)
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
//	AddUniform("spotLight.pointLight.base.color");
//	AddUniform("spotLight.pointLight.base.intensity");
//	AddUniform("spotLight.pointLight.atten.constant");
//	AddUniform("spotLight.pointLight.atten.linear");
//	AddUniform("spotLight.pointLight.atten.exponent");
//	AddUniform("spotLight.pointLight.position");
//	AddUniform("spotLight.pointLight.range");
//	AddUniform("spotLight.direction");
//	AddUniform("spotLight.cutoff");*/
//
//	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
//	m_uniforms[NORMAL_U] = glGetUniformLocation(m_program, "Normal");
//
//	m_uniforms[SPECI_U] = glGetUniformLocation(m_program, "specularIntensity");
//	m_uniforms[SPECP_U] = glGetUniformLocation(m_program, "specularPower");
//	m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
//
//	m_uniforms[SPOTLBC_U] = glGetUniformLocation(m_program, "spotLight.pointLight.base.color");
//	m_uniforms[SPOTLBI_U] = glGetUniformLocation(m_program, "spotLight.pointLight.base.intensity");
//	m_uniforms[SPOTLAC_U] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.constant");
//	m_uniforms[SPOTLAL_U] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.linear");
//	m_uniforms[SPOTLAE_U] = glGetUniformLocation(m_program, "spotLight.pointLight.atten.exponent");
//	m_uniforms[SPOTLP_U] = glGetUniformLocation(m_program, "spotLight.pointLight.position");
//	m_uniforms[SPOTLR_U] = glGetUniformLocation(m_program, "spotLight.pointLight.range");
//	m_uniforms[SPOTLD_U] = glGetUniformLocation(m_program, "spotLight.direction");
//	m_uniforms[SPOTLC_U] = glGetUniformLocation(m_program, "spotLight.cutoff");
//
//}
//
//void ForwardSpot::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
//{;
//	glm::mat4 Normal = transform.GetModel();
//	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
//	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetTransformedPos();
//	glm::vec3 ambient = renderingEngine->GetAmbientLight();
//	material.GetTexture("diffuse")->Bind(0);
//
//	spotLight sLight = *(spotLight*)renderingEngine->GetActiveLight();
//
//	glm::vec3 spotColor = sLight.m_color;
//	glm::vec3 spotPos = sLight.GetTransform().GetTransformedPos();
//	glm::vec3 spotDir = sLight.GetTransform().GetTransformedForward();
//
//	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
//	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);
//
//	glUniform1f(m_uniforms[SPECI_U], (float)material.GetFloat("specularIntensity"));
//	glUniform1f(m_uniforms[SPECP_U], (float)material.GetFloat("specularPower"));
//	glUniform3fv(m_uniforms[EYEPOS_U], 1, &eyePos[0]);
//
//	glUniform3fv(m_uniforms[SPOTLBC_U], 1, &spotColor[0]);
//	glUniform3fv(m_uniforms[SPOTLP_U], 1, &spotPos[0]);
//	glUniform3fv(m_uniforms[SPOTLD_U], 1, &spotDir[0]);
//
//	glUniform1f(m_uniforms[SPOTLBI_U], (float)sLight.m_intensity);
//	glUniform1f(m_uniforms[SPOTLAC_U], (float)sLight.atten.m_constant);
//	glUniform1f(m_uniforms[SPOTLAE_U], (float)sLight.atten.m_exponent);
//	glUniform1f(m_uniforms[SPOTLAL_U], (float)sLight.atten.m_linear);
//	glUniform1f(m_uniforms[SPOTLR_U], (float)sLight.range);
//	glUniform1f(m_uniforms[SPOTLC_U], (float)sLight.cutoff);
//
//}

