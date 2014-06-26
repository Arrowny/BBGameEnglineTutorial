#pragma once
#include "window.h"
#include "game.h"
#include "input.h"

class CoreEngine
{
public:
	CoreEngine(double frameRate, Window* window, Game* game);

	void start();
	void stop();
protected:
private:
	bool isRunning;
	Input* m_input;
	Window* m_window;
	Game* m_game;


	double m_frameTime;

	double SECOND = 1000000000l;
};

