#include <iostream>
#include "window.h"
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "coreEngine.h"
#include "testGame.h"
#include "phongShader.h"
#include "Lights.h"


#define WIDTH 800
#define HEIGHT 600

#define TITLE "3D_Game_Engine"


int main(int argc, char** argv)
{
	std::cout << "Start 3D game engine" << std::endl;

	Window window(WIDTH, HEIGHT, TITLE);
	TestGame* game = new TestGame();
	CoreEngine core(&window, game);
	core.start();
	return 0;
}