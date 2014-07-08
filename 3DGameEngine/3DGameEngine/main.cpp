#include <iostream>
#include "window.h"
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
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
	PhongShader* pShader = new PhongShader("./res/shaders/phongShader", glm::vec3(0.1,0.1,0.1));
	pShader->m_dLight = DirectionalLight(BaseLight(glm::vec3(1, 1, 1), .8), glm::vec3(0, 1, 0));
	Game game(pShader, WIDTH, HEIGHT);
	CoreEngine core(double(FRAME_CAP), &window, &game);
	core.start();
	return 0;
}