#pragma once
#include "window.h"
#include "testGame.h"
#include "input.h"
#include "shader.h"
#include "forwardAmbient.h"
#include "timing.h"
#include "renderingEngine.h"

class CoreEngine
{
public:
	CoreEngine(Window* window, Game* game);

	void start();
	void stop();
protected:
private:
	CoreEngine(const CoreEngine& other) {}
	void operator=(const CoreEngine& other) {}

	void UpdateWindowAndInput();

	bool isRunning;
	Input* m_input;
	Window* m_window;
	Game* m_game;
	Shader* m_shader;
	double m_frameTime;

	RenderingEngine m_renderingEngine;
};

