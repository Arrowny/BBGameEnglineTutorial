#include "coreEngine.h"
#include "timing.h"
#include "util.h"

#include <iostream>


CoreEngine::CoreEngine(double frameRate, Window* window):
m_window(window),
m_frameTime(double(1.0)/frameRate)
{
	isRunning = false;
}

void CoreEngine::start()
{
	if (isRunning) { return; }

	int frames = 0;
	double frameCounter = 0.0;

	isRunning = true;

	double lastTime = Time::GetTime();
	double unprocessedTime = 0;

	while (isRunning)
	{
		bool render = false;

		double startTime = Time::GetTime();
		double passedTime = startTime - lastTime;
		lastTime = Time::GetTime();

		unprocessedTime += passedTime;
		frameCounter += passedTime;

		while (unprocessedTime > m_frameTime)
		{
			render = true;
			unprocessedTime -= m_frameTime;
			if (m_window->isClosed()){ stop(); }

			//TODO: Update Game

			if (frameCounter > 1.0)
			{
				std::cout << "Frames/Second: " << frames << std::endl;
				frames = 0;
				frameCounter = 0.0;
			}
		}

		if (render) 
		{ 
			m_window->Render(); 
			frames++;
		}
		else { Util::Sleep(1); }
		
	}
}

void CoreEngine::stop()
{
	if (!isRunning){ return; }

	isRunning = false;
}


