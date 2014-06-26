#include <iostream>
#include "window.h"
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "coreEngine.h"
#include "game.h"
#include <iostream>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3D_Game_Engine"


int main(int argc, char** argv)
{

	std::cout << "Start 3D game engine" << std::endl;
	Window window(WIDTH, HEIGHT, TITLE);
	Game game;
	CoreEngine core(double(5000.0), &window, &game);
	core.start();
	return 0;
}