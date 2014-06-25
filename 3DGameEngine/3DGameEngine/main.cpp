#include <iostream>
#include "window.h"
#include <SDL\SDL.h>
#include <GL\glew.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3D_Game_Engine"

void init()
{
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
}

int main(int argc, char** argv)
{

	Window window(WIDTH, HEIGHT, TITLE);

	init();
	while (!window.isClosed())
	{
		window.Clear();
		window.SwapBuffers();
		window.Update();
	}

	return 0;
}