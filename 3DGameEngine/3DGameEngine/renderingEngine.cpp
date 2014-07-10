#include "renderingEngine.h"
#include "Shader.h"
#include <GL/glew.h>

renderingEngine::renderingEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
}

renderingEngine::~renderingEngine()
{
	//dtor
}

void renderingEngine::Render(gameObject* object)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object->render();
}