#include "coreEngine.h"
#include "timing.h"
#include "util.h"
#include <iostream>

#define FRAME_CAP 5000


CoreEngine::CoreEngine(Window* window, Game* game) :
m_frameTime(double(1.0) / FRAME_CAP),
m_window(window),
m_game(game)
{
	m_game->Init(window);
	m_input = new Input(m_window);
	Time::DELTA = m_frameTime;
	isRunning = false;

	//TODO:: comprise shader information somewhere more sensible
	//set up lighting
	PointLight TestPointLight1(BaseLight(glm::vec3(0, 1, 0), .8), Attenuation(0, 0, .01), glm::vec3(3.0, 0.0, 0.0), 10.0);
	PointLight TestPointLight2(BaseLight(glm::vec3(1, 0, 0), .8), Attenuation(0, 0, .01), glm::vec3(-3.0, 0.0, 0.0), 10.0);
	std::vector<PointLight> TestPointLights;
	SpotLight TestSpotLight1(PointLight(BaseLight(glm::vec3(0, 1, 0), .8), Attenuation(0, 0, .1), glm::vec3(0.0, 0.0, 0.0), 10.0), glm::vec3(0, 0, 1), 0.7);
	SpotLight TestSpotLight2(PointLight(BaseLight(glm::vec3(1, 0, 0), .8), Attenuation(0, 0, .1), glm::vec3(-3.0, 0.0, 0.0), 10.0), glm::vec3(0, 0, 1), 0.7);
	std::vector<SpotLight> TestSpotLights;
	m_shader = new PhongShader("./res/shaders/phongShader", glm::vec3(0.2, 0.2, 0.2));
	m_shader->m_dLight = DirectionalLight(BaseLight(glm::vec3(1, 1, 1), .8), glm::vec3(0, 1, 0));

	//m_shader->m_pointLights.push_back(TestPointLight1);
	//m_shader->m_pointLights.push_back(TestPointLight2);

	m_shader->m_spotLights.push_back(TestSpotLight1);
	m_shader->m_spotLights.push_back(TestSpotLight2);
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

			//DEBUG: Display information
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
			m_renderingEngine.RenderGameObject(&m_game->m_root, m_shader);
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


