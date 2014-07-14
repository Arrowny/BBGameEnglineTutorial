#include "coreEngine.h"
#include "Window.h"
#include "Timing.h"
#include "Game.h"
#include "RenderUtil.h"
#include <stdio.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Mesh.h"

coreEngine::coreEngine(TestGame* game, int width, int height, double frameRate) :
m_game(game),
//m_renderUtil(renderUtil),
width(width),
height(height),
m_frameTime(1.0 / frameRate)
{	
	m_isRunning = false;
}

coreEngine::~coreEngine()
{
}

void coreEngine::InitializeRenderingSystem()
{
	std::cout << m_renderUtil->getOpenGLVersion() << std::endl;
	m_renderUtil = new RenderUtil();
	m_renderUtil->initGraphics();
}

void coreEngine::CreateWindow(std::string title)
{
	m_window = new Window(width, height, title);
	InitializeRenderingSystem();
}

void coreEngine::Start()
{
	if (m_isRunning)
	{
		return;
	}

	std::cout << "In the coreStart" << std::endl;

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
	std::cout << "In the coreRun" << std::endl;
	m_isRunning = true;

	int frames = 0;
	double frameCounter = 0;

	m_game->init();

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

			unprocessedTime -= m_frameTime;
			

			if (m_window->isClosed())
			{
				Stop();
			}

			m_game->input(m_window->GetInput());
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
	//std::cout << "In the coreRender" << std::endl;
	
	//m_renderUtil->clearScreen();
	m_window->Render();
	m_game->render();

	m_window->SwapBuffers();
}

void coreEngine::cleanUp()
{
	m_window->Dispose();
}