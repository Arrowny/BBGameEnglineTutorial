#include "forwardAmbient.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardAmbient::ForwardAmbient(const std::string& fileName)
{
	std::string vertexShaderText = LoadShader(fileName + ".vs");
	std::string fragmentShaderText = LoadShader(fileName + ".fs");

	m_shaders[0] = CreateShader(vertexShaderText, GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(fragmentShaderText, GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++){
		glAttachShader(m_program, m_shaders[i]);
	}

	AddAllAttributes(vertexShaderText);

	CompileShader();

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[AMBIENTL_U] = glGetUniformLocation(m_program, "ambientLight");
}

void ForwardAmbient::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	glm::mat4 Normal = transform.GetModel();
	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetTransformedPos();
	glm::vec3 ambient = renderingEngine->GetAmbientLight();
	material.GetTexture("diffuse")->Bind(0);

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniform3fv(m_uniforms[AMBIENTL_U], 1, &ambient[0]);
}