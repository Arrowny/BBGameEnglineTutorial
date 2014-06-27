#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "RenderUtil.h"
#include "Mesh.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	//Create new window with (Width, Height, Title)
	Window window(WIDTH, HEIGHT, TITLE);

	Vertex vertices[] = { Vertex(glm::vec3(-0.8, -0.8, 0.0)),
						  Vertex(glm::vec3(0.0, 0.8, 0)),
						  Vertex(glm::vec3(0.8, -0.8, 0)), };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("./res/basicShader");
	Game game(&mesh, &shader);
	RenderUtil renderUtil;
	renderUtil.initGraphics();
	
	coreEngine core(&game, &renderUtil, &window,FRAME_CAP);
	core.Start();

	//std::cin.get();

	return 0;
}