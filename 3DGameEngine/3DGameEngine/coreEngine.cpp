#include "coreEngine.h"
#include "Window.h"
#include "Timing.h"
#include "Game.h"
#include "RenderUtil.h"
#include <stdio.h>

coreEngine::coreEngine(Game* game, RenderUtil* renderUtil, Window* window, Mesh* mesh, Shader* shader, double frameRate) :
m_game(game),
m_renderUtil(renderUtil),
m_window(window),
m_mesh(mesh),
m_shader(shader),
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
		frameCounter += passedTime;

		if (frameCounter >= 1.0){

			//::cout << "Frames/sec:" << frames << std::endl;
			frames = 0;
			frameCounter = 0;

		}

		while (unprocessedTime > m_frameTime){

			render = true;
			m_window->Update();

			unprocessedTime -= m_frameTime;
			

			if (m_window->isClosed())
			{
				Stop();
			}

			m_game->input();
			m_game->update();

			Time::setDelta(m_frameTime);

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
	m_window->Color(1.0f, 0.5f, 0.3f, 0.5f);
	m_game->render();
	m_shader->Bind();
	m_mesh->Draw();
	m_window->swapBuffers();
}

void coreEngine::cleanUp()
{
	m_window->Dispose();
}