#include "Lights.h"
#include "RenderingEngine.h"
#include "ForwardDirectional.h"


void BaseLight::AddToRenderingEngine(RenderingEngine* renderingEngine) 
{
	renderingEngine->AddLight(this);
}

//void PointLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
//{
//	renderingEngine->AddPointLight(*this);
//}
//
//void SpotLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
//{
//	renderingEngine->AddSpotLight(*this);
//}

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity,  glm::vec3 direction) :
BaseLight(color, intensity),
direction(glm::normalize(direction))
{
	SetShader(ForwardDirectional::GetInstance());
}
