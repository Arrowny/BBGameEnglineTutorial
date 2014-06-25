#include <iostream>
#include "window.h"
#include <SDL\SDL.h>
#include <GL\glew.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3D_Game_Engine"
#include "coreEngine.h"

int main(int argc, char** argv)
{

	Window window(WIDTH, HEIGHT, TITLE);
	CoreEngine core(5000.0, &window);
	core.start();
	return 0;
}