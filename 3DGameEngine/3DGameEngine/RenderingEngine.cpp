#include "RenderingEngine.h"
#include "BasicShader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
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
	directionalLight = DirectionalLight(BaseLight(glm::vec3(1, 0, 0), 0.2f), glm::vec3(1, 1, 1));
	directionalLight2 = DirectionalLight(BaseLight(glm::vec3(1, 1, 0), 0.4f), glm::vec3(-1, 1, -1));
	pointLight = PointLight(BaseLight(glm::vec3(0, 0, 1), 0.8f), Attenuation(0.0, 0.0, 0.1), glm::vec3(0, 0, 7), 100);

	object->render(ForwardAmbient::GetInstance(),this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL); //only do pixel lighting calculation

	object->render(ForwardDirectional::GetInstance(), this);

	DirectionalLight temp = directionalLight;
	directionalLight = directionalLight2;
	directionalLight2 = temp;

	object->render(ForwardDirectional::GetInstance(), this);

	temp = directionalLight;
	directionalLight = directionalLight2;
	directionalLight2 = temp;

	object->render(ForwardPoint::GetInstance(), this);

	glDepthFunc(GL_LESS);
	glDepthMask(true); 
	glDisable(GL_BLEND);
}


//const GLubyte* RenderingEngine::getOpenGLVersion()
//{
//	return glGetString(GL_VERSION);
//}