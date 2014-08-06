#include <iostream>
#include <GL/glew.h>
#include "renderingEngine.h"
#include "gameObject.h"
#include "Shader.h"
#include "skyBoxRenderer.h"
#include "particleSystem.h"

RenderingEngine::RenderingEngine()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);

	m_activeLight = new BaseLight();

	SetVector3f("ambientLight", glm::fvec3(0.1f, 0.1f, 0.1f));
	m_ambientShader = new Shader("forwardAmbient");
	m_baseParticleShader = NULL; //TODO: design overall basic particle shader;

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

	for (unsigned int ii = 0; ii < m_lights.size(); ii++)
	{
		m_activeLight = m_lights[ii];
		object->renderAll(m_activeLight->GetShader(), this);
	}

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);

	if (m_skyBox != NULL)
	{
		m_skyBox->renderSkyBox(this);
	}

	//Particles should be rendered last
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(0);
	//glEnable(GL_NORMALIZE);
	//glColor4f(.1, .8, .8, 0.1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//TODO: currently baseParticleShader does nothing. Add functionality.
	for (unsigned int ii = 0; ii < m_particles.size(); ii++)
	{
		m_particles[ii]->renderParticles(m_baseParticleShader, this);
	}
	glDepthMask(1);
	glDisable(GL_BLEND);
}