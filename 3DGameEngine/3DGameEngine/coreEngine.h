#pragma once
#include "window.h"

class CoreEngine
{
public:
	CoreEngine(double frameRate, Window* window);

	void start();
	void stop();
protected:
private:
	bool isRunning;
	Window* m_window;
	double m_frameTime;

	double SECOND = 1000000000l;
};

