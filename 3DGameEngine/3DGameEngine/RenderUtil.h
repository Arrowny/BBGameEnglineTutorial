#pragma once

#include <iostream>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class RenderUtil
{
public:
	RenderUtil();
	~RenderUtil();
	
	void clearScreen();
	void initGraphics();
	char* getOpenGLVersion();


protected:
private:

};

