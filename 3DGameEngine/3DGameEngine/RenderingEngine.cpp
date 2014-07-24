#include "RenderingEngine.h"
#include "BasicShader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"
#include "Window.h"
#include "GameObject.h"



RenderingEngine::RenderingEngine()
{

	//glClearColor(2.0f, 1.5f, 0.0f, 0.5f);
	//glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_CLAMP);

	mainCamera = new Camera(10.0f, 1.0, 1.0, 1000.0);
	
	AddVector("ambientIntensity", glm::fvec3(0.2f, 0.2f, 0.2f));
	m_samplerMap.insert(std::pair<std::string, unsigned int>("diffuse", 0));
	m_shaderAmbient = new Shader("./res/shader/forwardAmbient");
}


RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::input(Input input, float delta)
{
	mainCamera->input(input, delta);
}

void RenderingEngine::render(GameObject* object)
{
	//lights.clear();
	//object->AddToRenderingEngine(this);

	object->render(m_shaderAmbient,this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL); //only do pixel lighting calculation

	for each (BaseLight* light in lights)
	{
		activeLight = light;
		object->render(light->GetShader(), this);
	}


	glDepthFunc(GL_LESS);
	glDepthMask(true); 
	glDisable(GL_BLEND);
}

void RenderingEngine::AddLight(BaseLight* light)
{
	lights.push_back(light);
}

BaseLight* RenderingEngine::GetActiveLight()
{
	return activeLight;
}

void RenderingEngine::AddCamera(Camera* camera) { mainCamera = camera; }