#include "RenderUtil.h"


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

	std::cout << getOpenGLVersion() << std::endl;

	//glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);

}

char* RenderUtil::getOpenGLVersion(){

	return (char*)glGetString(GL_VERSION);

}