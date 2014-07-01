#include "coreEngine.h"
#include "timing.h"
#include "util.h"

#include <iostream>


CoreEngine::CoreEngine(double frameRate, Window* window, Game* game):
m_window(window),
m_frameTime(double(1.0)/frameRate),
m_game(game)
{
	m_input = new Input(m_window);
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

		if (m_window->isClosed()){ stop(); }

		while (unprocessedTime > m_frameTime)
		{
			render = true;

			UpdateWindowAndInput();
			m_game->ProcessInput(m_input);
			m_game->Update();

			unprocessedTime -= m_frameTime;

			//Debug:
			if (frameCounter > 1.0)
			{
				std::cout << "Frames/Second: " << frames << std::endl;
				frames = 0;
				frameCounter = 0.0;
			}
		}

		if (render) 
		{ 
			m_game->Render();
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

void CoreEngine::UpdateWindowAndInput()
{
	m_input->Clear();
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		m_window->Update(e);
		m_input->Update(e);
	}
}


