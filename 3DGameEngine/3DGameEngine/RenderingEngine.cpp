#include "RenderingEngine.h"
#include "BasicShader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"
#include "Window.h"
#include "GameObject.h"


RenderingEngine::RenderingEngine():
mainCamera(glm::vec3(0, 1, -4), 70.0f, (float)WindowParameter::width / (float)WindowParameter::height, 1.0f, 1000.0f)
{

	//glClearColor(2.0f, 1.5f, 0.0f, 0.5f);
	//glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_CLAMP);

	//	glEnable(GL_FRAMEBUFFER_SRGB);// it is already rgb colors so we do not need to do sth to it
}


RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::input(Input input, float delta)
{
	mainCamera.Input(input, delta);
}

void RenderingEngine::render(GameObject* object)
{
	ClearLightList();

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

	for each (DirectionalLight light in directionalLights)
	{
		activeDirectionalLight = light;
		object->render(ForwardDirectional::GetInstance(), this);
	}

	for each (PointLight light in pointLights)
	{
		activePointLight = light;
		object->render(ForwardPoint::GetInstance(), this);
	}

	//for each (SpotLight light in spotLights)
	//{
	//	activeSpotLight = light;
	//	object->render(ForwardSpot::GetInstance(), this);
	//}


	glDepthFunc(GL_LESS);
	glDepthMask(true); 
	glDisable(GL_BLEND);
}


//const GLubyte* RenderingEngine::getOpenGLVersion()
//{
//	return glGetString(GL_VERSION);
//}

void RenderingEngine::AddDirectionalLight(DirectionalLight directionalLight)
{
	directionalLights.push_back(directionalLight);
}
void RenderingEngine::AddPointLight(PointLight pointLight)
{
	pointLights.push_back(pointLight);
}
void RenderingEngine::AddSpotLight(SpotLight spotLight)
{
	spotLights.push_back(spotLight);
}

void RenderingEngine::ClearLightList()
{
	directionalLights.clear();
	pointLights.clear();
}