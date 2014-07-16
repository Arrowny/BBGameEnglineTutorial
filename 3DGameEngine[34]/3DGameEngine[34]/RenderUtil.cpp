#include "RenderUtil.h"
#include <String>

RenderUtil::RenderUtil()
{
}


RenderUtil::~RenderUtil()
{
}

void RenderUtil::clearScreen(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void RenderUtil::initGraphics(){

	//glClearColor(2.0f, 1.5f, 0.0f, 0.5f);
	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

//	glEnable(GL_FRAMEBUFFER_SRGB);// it is already rgb colors so we do not need to do sth to it

}

const GLubyte* RenderUtil::getOpenGLVersion()
{
	return glGetString(GL_VERSION);
}