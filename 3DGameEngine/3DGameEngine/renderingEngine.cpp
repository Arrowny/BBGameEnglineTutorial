#include "renderingEngine.h"
#include "Shader.h"
#include <GL/glew.h>

renderingEngine::renderingEngine()
{
	std::cout << getOpenGLVersion() << std::endl;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);
}

renderingEngine::~renderingEngine()
{
	//dtor
}

void renderingEngine::Render(gameObject* object)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object->render(Shader::GetInstance());
}

char* renderingEngine::getOpenGLVersion(){

	return (char*)glGetString(GL_VERSION);

}