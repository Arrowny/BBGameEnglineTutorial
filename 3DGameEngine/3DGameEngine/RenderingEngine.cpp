#include "RenderingEngine.h"
#include "BasicShader.h"
#include "Window.h"
#include "GameObject.h"

RenderingEngine::RenderingEngine():
mainCamera(glm::vec3(0, 1, -4), 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f)
{

	//glClearColor(2.0f, 1.5f, 0.0f, 0.5f);
	//glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_CLAMP);

	//	glEnable(GL_FRAMEBUFFER_SRGB);// it is already rgb colors so we do not need to do sth to it
}


RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::input(Input input, float delta)
{
	mainCamera.Input(input, delta);
}
void RenderingEngine::render(GameObject* object)
{
	object->render(BasicShader::GetInstance(),this);
}


//const GLubyte* RenderingEngine::getOpenGLVersion()
//{
//	return glGetString(GL_VERSION);
//}