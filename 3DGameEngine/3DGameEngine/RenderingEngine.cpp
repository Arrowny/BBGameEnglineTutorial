#include "RenderingEngine.h"
#include "BasicShader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"
#include "Window.h"
#include "GameObject.h"



RenderingEngine::RenderingEngine()/*:
mainCamera(70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f)*/
{

	//glClearColor(2.0f, 1.5f, 0.0f, 0.5f);
	//glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_CLAMP);

	mainCamera = new Camera(10.0f, 1.0, 1.0, 1000.0);

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
	lights.clear();
	object->AddToRenderingEngine(this);

	/*activeDirectionalLight = DirectionalLight(BaseLight(glm::vec3(1, 0, 0), 0.2f), glm::vec3(1, 1, 1));
	directionalLight2 = DirectionalLight(BaseLight(glm::vec3(1, 1, 0), 0.4f), glm::vec3(-1, 1, -1));
	activePointLight = PointLight(BaseLight(glm::vec3(0, 1, 1), 0.4f), Attenuation(0.0, 0.0, 0.1), glm::vec3(0, 0, 7), 30);
	activeSpotLight = SpotLight(PointLight(BaseLight(glm::fvec3(0.0, 0.0, 1.0), 0.6f), Attenuation(0.0, 0.0, 0.1), glm::fvec3(-2.0, 0.0, 0.0), 30), glm::fvec3(1.0, 1.0, 1.0), 0.1f);*/


	object->render(ForwardAmbient::GetInstance(),this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL); //only do pixel lighting calculation

	for each (BaseLight* light in lights)
	{
		light->GetShader()->SetRenderingEngine(this);
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