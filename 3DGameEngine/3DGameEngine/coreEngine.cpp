#include "coreEngine.h"
#include "Timing.h"
#include "Game.h"
#include <stdio.h>

CoreEngine::CoreEngine(Game* game, RenderingEngine* renderingEngine, PhysicsEngine* physicEngine, Window* window, double frameRate) :
m_game(game),
m_window(window),
m_frameTime(1.0 / frameRate),
m_renderingEngine(renderingEngine),
m_physicsEngine(physicEngine)
{
	std::cout <<"OpenGL version: " << getOpenGLVersion() << std::endl;
	m_isRunning = false;
	m_game->SetEngine(this);
}

CoreEngine::~CoreEngine()
{
	m_window->Dispose();
}

void CoreEngine::Start()
{
	if (m_isRunning)
	{
		return;
	}

	Run();
}

void CoreEngine::Stop()
{
	if (!m_isRunning)
	{
		return;
	}

	m_isRunning = false;
}

void CoreEngine::Run(){

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

			m_game->input(m_window->GetInput(), m_frameTime);
			m_game->update(m_frameTime);

			unprocessedTime -= m_frameTime;

		}

		if (render)
		{
			m_game->updatePhysics(m_physicsEngine);
			Render();
			frames++;
		}

		else
		{
			SDL_Delay(1);
		}

	}

	cleanUp();
}

void CoreEngine::Render()
{
	m_game->render(m_renderingEngine);
	m_window->swapBuffers();
}

void CoreEngine::cleanUp()
{
	m_window->Dispose();
}

char* CoreEngine::getOpenGLVersion()
{
	return (char*)glGetString(GL_VERSION);
}