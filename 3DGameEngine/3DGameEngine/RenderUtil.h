#pragma once

#include <iostream>
#include <GL\glew.h>
#include <SDL\SDL.h>

class RenderUtil
{
public:
	RenderUtil();
	~RenderUtil();
	
	void clearScreen();
	void initGraphics();
	const GLubyte* getOpenGLVersion();

protected:
private:

};

