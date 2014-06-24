#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	//Create new window with (Width, Height, Title)
	Window window(WIDTH, HEIGHT, "3DGameEngine");

	while (!window.isClosed()){

		window.Color(1.0f, 0.5f, 0.3f, 0.5f);
		window.Update();

	}

	return 0;
}