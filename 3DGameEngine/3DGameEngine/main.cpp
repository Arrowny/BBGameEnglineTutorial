#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "RenderUtil.h"
#include "Mesh.h"
#include "Shader.h"



#define WIDTH 600
#define HEIGHT 600
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	Window window(WIDTH, HEIGHT, TITLE);

	WindowParameter::width = WIDTH;
	WindowParameter::height = HEIGHT;

	Vertex vertices[] = { Vertex(glm::vec3(-1.0, -1.0, 0.0)),
						  Vertex(glm::vec3(0.0, 1.0, 0.0)),
						  Vertex(glm::vec3(1.0, -1.0, 0.0)), 
						  Vertex(glm::vec3(0.0, -1.0, 1.0)),
						  Vertex(glm::vec3(0.0,-1.0,-1.0))};

	unsigned int indices[] = {	0, 3, 1,
								3, 2, 1,
								0, 2, 3,
								0, 4, 2,
								0, 1, 4,
								4, 1, 2};


	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh("./res/cube.obj");
	Shader shader("./res/basicShader");
	Transform transform;
	Camera camera(glm::vec3(0, 0, -4), 70.0f, (float)WIDTH / (float)HEIGHT, 1.0f, 1000.0f);

	//Game game;
	Game game(&mesh, &shader, transform, camera);
	RenderUtil renderUtil;
	renderUtil.initGraphics();
	coreEngine core(&game, &renderUtil, &window, FRAME_CAP);
	core.Start();

	return 0;
}