#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "renderingEngine.h"

#define WIDTH 1000
#define HEIGHT 800
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	Window window(WIDTH, HEIGHT, TITLE);
	renderingEngine renderingEngine;
	Game game;

	coreEngine core(&game, &renderingEngine, &window, FRAME_CAP);

	core.Start();

	return 0;
}
