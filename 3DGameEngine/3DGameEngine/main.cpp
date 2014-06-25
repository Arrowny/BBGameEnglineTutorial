#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "RenderUtil.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	Game game;
	RenderUtil renderUtil;
	renderUtil.initGraphics();
	//Create new window with (Width, Height, Title)
	Window window(WIDTH, HEIGHT, TITLE);
	coreEngine core(&game, &renderUtil, &window, FRAME_CAP);
	
	core.Start();

	//std::cin.get();

	return 0;
}