#include <iostream>
#include "window.h"
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "coreEngine.h"
#include "game.h"
#include "phongShader.h"
#include <iostream>

#define WIDTH 800
#define HEIGHT 600
#define FRAME_CAP 5000
#define TITLE "3D_Game_Engine"


int main(int argc, char** argv)
{
	std::cout << "Start 3D game engine" << std::endl;

	Window window(WIDTH, HEIGHT, TITLE);
	Shader* shader = new PhongShader("./res/shaders/shader");
	Game game(shader,WIDTH,HEIGHT);
	CoreEngine core(double(FRAME_CAP), &window, &game);
	core.start();
	return 0;
}