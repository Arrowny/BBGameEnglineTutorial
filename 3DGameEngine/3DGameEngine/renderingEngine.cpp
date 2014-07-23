#include "renderingEngine.h"
#include <iostream>
#include "gameObject.h"
#include "shader.h"


RenderingEngine::RenderingEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);

	m_ambientShader = new Shader("forward_ambient");

	m_samplerMap["diffuse"] = 0;
	//m_samplerMap["normal"] = 0; TODO: add capability to include normal maps

	addVector("ambientIntensity", glm::vec3(0.2, 0.2, 0.2));
}

RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::RenderGameObject(GameObject* gameObject)
{

	gameObject->Render(m_ambientShader, this);

	glEnable(GL_BLEND); glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false); glDepthFunc(GL_EQUAL);

	for (int ii = 0; ii < m_lights.size(); ii++)
	{
		activeLight = m_lights[ii];
		gameObject->Render(m_lights[ii]->m_shader, this);
	}

	glDepthFunc(GL_LESS); glDepthMask(true);
	glDisable(GL_BLEND);
}

int RenderingEngine::getSamplerSlot(std::string samplerName)
{
	if (m_samplerMap.find(samplerName) != m_samplerMap.end())
	{
		return m_samplerMap[samplerName];
	}
	else
	{
		std::cerr << "Error: unknown sampler name: " << samplerName << std::endl;
		exit(1);
	}
}

std::string RenderingEngine::getOpenGLVersion()
{
	return (const char*)glGetString(GL_VERSION);
}

void RenderingEngine::setUniformStruct(const glm::mat4& worldMatrix, Material& mat, Shader* shader, std::string uniformName, std::string uniformType)
{
	std::cerr << "Error: unknown component of renderingEngine: " << uniformName << "." << std::endl;
	exit(1);
}
