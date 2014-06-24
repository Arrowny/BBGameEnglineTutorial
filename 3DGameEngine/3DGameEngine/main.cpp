#include <iostream>
#include "window.h"
#include <GL\glew.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3D_Game_Engine"

int main()
{

	Window window(WIDTH, HEIGHT, TITLE);

	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	while (!window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	system("pause");
	return 0;
}