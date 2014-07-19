#include "forwardPoint.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardPoint::ForwardPoint()
{
	AddVertexShaderFromFile("./res/forwardPoint.vs");
	AddFragmentShaderFromFile("./res/forwardPoint.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);

	CompileShader();

	AddUniform("transform");
	AddUniform("Normal");
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
	AddUniform("pointLight.base.color");
	AddUniform("pointLight.base.intensity");
	AddUniform("pointLight.atten.constant");
	AddUniform("pointLight.atten.linear");
	AddUniform("pointLight.atten.exponent");
	AddUniform("pointLight.position");
	AddUniform("pointLight.range");
}

void ForwardPoint::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 worldMatrix = transform.GetModel();
	glm::mat4 projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.GetTexture("diffuse")->Bind(0);

	SetUniform("Normal", worldMatrix);
	SetUniform("transform", projectedMatrix);

	SetUniform("eyePos", renderingEngine->GetMainCamera().GetTransform().GetTransformedPos());
	SetUniformf("specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformf("specularPower", material.GetFloat("specularPower"));

	pointLight pLight = *(pointLight*)renderingEngine->GetActiveLight();

	SetUniform("pointLight.base.color", pLight.m_color);
	SetUniformf("pointLight.base.intensity", pLight.m_intensity);
	SetUniformf("pointLight.atten.constant", pLight.atten.m_constant);
	SetUniformf("pointLight.atten.linear", pLight.atten.m_linear);
	SetUniformf("pointLight.atten.exponent", pLight.atten.m_exponent);
	SetUniform("pointLight.position", pLight.GetTransform().GetTransformedPos());
	SetUniformf("pointLight.range", pLight.range);
}

//ForwardPoint::ForwardPoint(const std::string& fileName)
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
//	AddUniform("pointLight.base.color");
//	AddUniform("pointLight.base.intensity");
//	AddUniform("pointLight.atten.constant");
//	AddUniform("pointLight.atten.linear");
//	AddUniform("pointLight.atten.exponent");
//	AddUniform("pointLight.position");
//	AddUniform("pointLight.range");*/
//	
//	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
//	m_uniforms[NORMAL_U] = glGetUniformLocation(m_program, "Normal");
//
//	m_uniforms[SPECI_U] = glGetUniformLocation(m_program, "specularIntensity");
//	m_uniforms[SPECP_U] = glGetUniformLocation(m_program, "specularPower");
//	m_uniforms[EYEPOS_U] = glGetUniformLocation(m_program, "eyePos");
//
//	m_uniforms[POINTLBC_U] = glGetUniformLocation(m_program, "pointLight.base.color");
//	m_uniforms[POINTLBI_U] = glGetUniformLocation(m_program, "pointLight.base.intensity");
//	m_uniforms[POINTLAC_U] = glGetUniformLocation(m_program, "pointLight.atten.constant");
//	m_uniforms[POINTLAL_U] = glGetUniformLocation(m_program, "pointLight.atten.linear");
//	m_uniforms[POINTLAE_U] = glGetUniformLocation(m_program, "pointLight.atten.exponent");
//	m_uniforms[POINTLP_U] = glGetUniformLocation(m_program, "pointLight.position");
//	m_uniforms[POINTLR_U] = glGetUniformLocation(m_program, "pointLight.range");
//
//}
//
//void ForwardPoint::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
//{
//	glm::mat4 Normal = transform.GetModel();
//	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
//	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetTransformedPos();
//	glm::vec3 ambient = renderingEngine->GetAmbientLight();
//	material.GetTexture("diffuse")->Bind(0);
//
//	pointLight pLight = *(pointLight*)renderingEngine->GetActiveLight();
//
//	glm::vec3 pointColor = pLight.m_color;
//	glm::vec3 pointPos = pLight.GetTransform().GetTransformedForward();
//	
//	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
//	glUniformMatrix4fv(m_uniforms[NORMAL_U], 1, GL_FALSE, &Normal[0][0]);
//
//	glUniform1f(m_uniforms[SPECI_U], (float)material.GetFloat("specularIntensity"));
//	glUniform1f(m_uniforms[SPECP_U], (float)material.GetFloat("specularPower"));
//	glUniform3fv(m_uniforms[EYEPOS_U], 1, &eyePos[0]);
//
//	glUniform3fv(m_uniforms[POINTLBC_U], 1, &pointColor[0]);
//	glUniform3fv(m_uniforms[POINTLP_U], 1, &pointPos[0]);
//	glUniform1f(m_uniforms[POINTLBI_U], (float)pLight.m_intensity);
//	glUniform1f(m_uniforms[POINTLAC_U], (float)pLight.atten.m_constant);
//	glUniform1f(m_uniforms[POINTLAE_U], (float)pLight.atten.m_exponent);
//	glUniform1f(m_uniforms[POINTLAL_U], (float)pLight.atten.m_linear);
//	glUniform1f(m_uniforms[POINTLR_U], (float)pLight.range);
//
//}

