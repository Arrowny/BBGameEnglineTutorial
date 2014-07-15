#include "forwardAmbient.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

ForwardAmbient::ForwardAmbient(const std::string& fileName)
{
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++){
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	CompileShader();

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[AMBIENTL_U] = glGetUniformLocation(m_program, "ambientLight");
}

void ForwardAmbient::UpdateUniforms(const Transform& transform, const Material& material, renderingEngine* renderingEngine)
{
	//glm::mat4 model = transform.GetProjection(renderingEngine->GetMainCamera());
	glm::mat4 Normal = transform.GetModel();
	glm::mat4 model = renderingEngine->GetMainCamera().GetViewProjection() * Normal;
	//glm::vec3 eyePos = transform.GetCameraPos(renderingEngine->GetMainCamera());
	glm::vec3 eyePos = renderingEngine->GetMainCamera().GetTransform().GetPos();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniform3f(m_uniforms[AMBIENTL_U], (float)renderingEngine->GetAmbientLight()[0], (float)renderingEngine->GetAmbientLight()[1], (float)renderingEngine->GetAmbientLight()[2]);
}