#pragma once
#include "window.h"
#include "input.h"
#include "shader.h"
#include "timing.h"
#include "renderingEngine.h"

class Game;

class CoreEngine
{
public:
	CoreEngine(Window* window, Game* game);

	void start();
	void stop();

	RenderingEngine m_renderingEngine;

private:
	CoreEngine(const CoreEngine& other) {}
	void operator=(const CoreEngine& other) {}

	void UpdateWindowAndInput();

	bool isRunning;
	Input* m_input;
	Window* m_window;
	Game* m_game;
	double m_frameTime;

};

