#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "RenderUtil.h"
#include "Mesh.h"
#include "Texture.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	///////////////////////////////////////////Declarations///////////////////////////////////////////

	Window window(WIDTH, HEIGHT, TITLE);

	Vertex vertices[] = { Vertex(glm::vec3(-0.8, -0.8, 0.0), glm::vec2(1.0f, 0.0)),
						  Vertex(glm::vec3(0.0, 0.8, 0.0), glm::vec2(0.5f, 0.0)),
						  Vertex(glm::vec3(0.8, -0.8, 0.0), glm::vec2(1.0f, 0.0)),
						  Vertex(glm::vec3(0.0, -0.8, 0.8), glm::vec2(0.0, 0.5f)),
						  Vertex(glm::vec3(0.0, -0.8, -0.8), glm::vec2(0.0, 0.5f)) };

	unsigned int indices[] = { 3, 1, 0,
							   2, 1, 3,
							   0, 2, 3,
							   4, 1, 2,
							   1, 4, 0,
							   2, 0, 4 };

	Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//Mesh mesh("./res/cube.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/colour.jpg");

	RenderUtil renderUtil;
	Game game(&mesh, &shader, &camera, &texture);
	coreEngine core(&game, &renderUtil, &window, FRAME_CAP);

	///////////////////////////////////////////Core_Stuff////////////////////////////////////////////////
	
	renderUtil.initGraphics();
	core.Start();

	return 0;
}
