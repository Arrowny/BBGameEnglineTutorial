#include <iostream>
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "window.h"
#include "coreEngine.h"
#include "testGame.h"



#define WIDTH 800
#define HEIGHT 600

#define TITLE "3D_Game_Engine"


int main(int argc, char** argv)
{
	std::cout << "Start 3D game engine" << std::endl;

	Window window(WIDTH, HEIGHT, TITLE);
	Game* game = new TestGame(); //games must be initialized in this way or this will not work! Annoying bug that has to do with scoping problems and polymorphism.... or something.
	CoreEngine core(&window, game);
	core.start();
	return 0;
}