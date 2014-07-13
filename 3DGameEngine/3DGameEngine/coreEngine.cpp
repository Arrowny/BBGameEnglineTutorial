#include "coreEngine.h"
#include "Window.h"
#include "Timing.h"
#include "Game.h"
#include <stdio.h>

coreEngine::coreEngine(Game* game, renderingEngine* renderingEngine, Window* window, double frameRate) :
m_game(game),
m_window(window),
m_frameTime(1.0 / frameRate),
m_renderingEngine(renderingEngine)
{
	m_isRunning = false;
}

coreEngine::~coreEngine()
{
	m_window->Dispose();
	//if (m_renderingEngine) delete m_renderingEngine;
}

void coreEngine::Start()
{
	if (m_isRunning)
	{
		return;
	}

	Run();
}

void coreEngine::Stop()
{
	if (!m_isRunning)
	{
		return;
	}

	m_isRunning = false;
}

void coreEngine::Run(){

	m_isRunning = true;

	m_game->init();

	int frames = 0;
	double frameCounter = 0;

	double lastTime = Time::getTime();
	double unprocessedTime = 0;

	while (m_isRunning){

		bool render = false;

		double startTime = Time::getTime();
		double passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += passedTime;
		frameCounter += passedTime;

		if (frameCounter >= 1.0){

			std::cout << "Frames/sec:" << frames << std::endl;
			frames = 0;
			frameCounter = 0;

		}
		
		while (unprocessedTime > m_frameTime){

			render = true;
			m_window->Update();
			
			if (m_window->isClosed())
			{
				Stop();
			}

			m_game->input(m_frameTime);
			m_renderingEngine->input(m_window->GetInput(), m_frameTime);
			m_game->update(m_frameTime);

			unprocessedTime -= m_frameTime;

		}

		if (render){

			Render();
			frames++;
		}

		else{

			SDL_Delay(1);
		}

	}

	cleanUp();
}

void coreEngine::Render()
{
	m_renderingEngine->Render(&m_game->GetRoot());
	m_window->swapBuffers();
}

void coreEngine::cleanUp()
{
	m_window->Dispose();
}