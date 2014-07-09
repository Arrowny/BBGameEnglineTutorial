#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "RenderUtil.h"

#define WIDTH 1000
#define HEIGHT 800
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	///////////////////////////////////////////Declarations///////////////////////////////////////////

	Window window(WIDTH, HEIGHT, TITLE);
	RenderUtil renderUtil;
	Game game;

	coreEngine core(&game, &renderUtil, &window, FRAME_CAP);

	///////////////////////////////////////////Core_Stuff////////////////////////////////////////////
	
	renderUtil.initGraphics();
	core.Start();

	return 0;
}
