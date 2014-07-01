#pragma once
#include "window.h"
#include "game.h"
#include "input.h"
#include "shader.h"

class CoreEngine
{
public:
	CoreEngine(double frameRate, Window* window, Game* game, Shader* shader);

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

};

