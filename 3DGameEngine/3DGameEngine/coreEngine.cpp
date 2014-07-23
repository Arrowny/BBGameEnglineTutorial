#include "coreEngine.h"
#include "timing.h"
#include "util.h"
#include "testGame.h"
#include <iostream>

#define FRAME_CAP 5000


CoreEngine::CoreEngine(Window* window, Game* game) :
m_frameTime(double(1.0) / FRAME_CAP),
m_window(window),
m_game(game)
{
	m_game->setEngine(this);
	m_game->Init(window);
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
			m_game->ProcessInput(m_input, m_frameTime);
			//m_game->Update();

			unprocessedTime -= m_frameTime;

			//DEBUG: Display framerate information
			if (frameCounter > 1.0)
			{
				std::cout << "Frames/Second: " << frames << std::endl;
				frames = 0;
				frameCounter = 0.0;
			}
		}

		if (render) 
		{ 
			m_renderingEngine.Clear();
			m_game->Render(&m_renderingEngine);
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


