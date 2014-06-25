#pragma once
#include "window.h"

class CoreEngine
{
public:
	CoreEngine(Window* window);

	void start();
	void stop();
protected:
private:
	bool isRunning;
	Window* m_window;
};

