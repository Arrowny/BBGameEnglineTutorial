#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Window.h"
#include "coreEngine.h"
#include "Game.h"
#include "testGame.h"
#include "renderingEngine.h"

#define WIDTH 1200
#define HEIGHT 800
#define TITLE "3DGameEngine"
#define FRAME_CAP 5000.0

int main(int argc, char** argv)
{
	Window window(WIDTH, HEIGHT, TITLE);
	RenderingEngine renderingEngine;
	PhysicsEngine physicsEngine(1.0 / FRAME_CAP);
	TestGame game;

	CoreEngine core(&game, &renderingEngine, &physicsEngine, &window, FRAME_CAP);
	core.Start();

	return 0;
}
