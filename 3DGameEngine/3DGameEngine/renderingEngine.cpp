#include "renderingEngine.h"


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

void RenderingEngine::RenderGameObject(GameObject* gameObject, Shader* shader)
{
	gameObject->Render(shader);
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
