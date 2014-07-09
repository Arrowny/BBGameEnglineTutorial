#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "RenderUtil.h"





#define WIDTH 600
#define HEIGHT 600
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	Window window(WIDTH, HEIGHT, TITLE);

	WindowParameter::width = WIDTH;
	WindowParameter::height = HEIGHT;

	

	//Game game;
	Game game;
	RenderUtil renderUtil;
	renderUtil.initGraphics();
	coreEngine core(&game, &renderUtil, &window, FRAME_CAP);
	core.Start();

	return 0;
}