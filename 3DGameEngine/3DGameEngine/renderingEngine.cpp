#include <iostream>
#include <GL/glew.h>
#include "renderingEngine.h"
#include "gameObject.h"
#include "Shader.h"
#include "skyBoxRenderer.h"

RenderingEngine::RenderingEngine()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);

	m_activeLight = new BaseLight();

	SetVector3f("ambientLight", glm::fvec3(0.1f, 0.1f, 0.1f));
	m_ambientShader = new Shader("forwardAmbient");

	m_samplerMap["diffuse"] = 0; //set slot for diffuse texture
	m_skyBox = NULL;
}

RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::Render(GameObject* object)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	object->renderAll(m_ambientShader, this);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	for (unsigned int i = 0; i < m_lights.size(); i++)
	{
		m_activeLight = m_lights[i];
		object->renderAll(m_activeLight->GetShader(), this);
	}

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);

	if (m_skyBox != NULL)
	{
		m_skyBox->renderSkyBox(this);
	}
}