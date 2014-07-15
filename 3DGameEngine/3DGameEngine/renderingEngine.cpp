#include "renderingEngine.h"
#include <iostream>
#include "gameObject.h"
#include "shader.h"
#include "forwardAmbient.h"
#include "forwardDirectional.h"
#include "forwardPointLight.h"
#include "forwardSpotLight.h"


RenderingEngine::RenderingEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);

	m_ambientShader = new ForwardAmbient("forward_ambient", glm::vec3(0.2, 0.2, 0.2));
}

RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::RenderGameObject(GameObject* gameObject)
{
	gameObject->addToRenderingEngine(this);

	gameObject->Render(m_ambientShader, this);

	glEnable(GL_BLEND); glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false); glDepthFunc(GL_EQUAL);

	for (int ii = 0; ii < m_lights.size(); ii++)
	{
		activeLight = m_lights[ii];
		gameObject->Render(m_lights[ii]->m_shader, this);
	}
	m_lights.clear();

	glDepthFunc(GL_LESS); glDepthMask(true);
	glDisable(GL_BLEND);
}

void RenderingEngine::setTextures(bool enabled)
{
	if (enabled) { glEnable(GL_TEXTURE_2D);}
	else { glDisable(GL_TEXTURE_2D); }
}

std::string RenderingEngine::getOpenGLVersion()
{
	return (const char*)glGetString(GL_VERSION);
}

void RenderingEngine::updateCameraPerspective(double zNear, double zFar, double fov, double screenWidth, double screenHeight)
{
	if (m_camera != NULL) { m_camera->reinitPerspectiveMatrix(zNear, zFar, fov, screenWidth, screenHeight); }
	else
	{
		std::cerr << "Error: RenderingEngine was not initialized before perspective update in updateCameraPerspective of RenderingEngine." << std::endl;
		exit(1);
	}
}
