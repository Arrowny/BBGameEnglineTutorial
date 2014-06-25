#include "coreEngine.h"
#include "Window.h"
#include "Timing.h"
#include "Game.h"
#include "RenderUtil.h"
#include <stdio.h>

coreEngine::coreEngine(Game* game, RenderUtil* renderUtil, Window* window, double frameRate) :
m_game(game),
m_renderUtil(renderUtil),
m_window(window),
m_frameTime(1.0 / frameRate)
{
	m_isRunning = false;
}

coreEngine::~coreEngine()
{
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

		while (unprocessedTime > m_frameTime){

			m_game->input();
			m_game->update();

			render = true;

			unprocessedTime -= m_frameTime;
			frameCounter += passedTime;

			if (m_window->isClosed())
			{
				Stop();
			}

			Time::setDelta(m_frameTime);

			if (frameCounter >= 1.0){

				std::cout << "Frames/sec:" << frames << std::endl;
				frames = 0;
				frameCounter = 0;

			}
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
	m_renderUtil->clearScreen();
	m_game->render();
	m_window->Render();
}

void coreEngine::cleanUp()
{
	m_window->Dispose();
}