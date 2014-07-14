#include "renderingEngine.h"
#include <iostream>


RenderingEngine::RenderingEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);
}

RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::RenderGameObject(GameObject* gameObject, std::vector<Shader*> shaders)
{
	if ( (gameObject != NULL) && (shaders.size() > 0) ) 
	{ 
		gameObject->Render(shaders[0], m_camera);

		for (int ii = 1; ii < shaders.size(); ii++)
		{
			glEnable(GL_BLEND); glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(false); glDepthFunc(GL_EQUAL);
			gameObject->Render(shaders[ii], m_camera);
			glDepthFunc(GL_LESS); glDepthMask(true);
			glDisable(GL_BLEND);
		}
	}
	else if (gameObject == NULL)
	{
		std::cerr << "Error: gameObject not initialized in RenderGameObject method of RenderingEngine." << std::endl;
		exit(1);
	}
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
