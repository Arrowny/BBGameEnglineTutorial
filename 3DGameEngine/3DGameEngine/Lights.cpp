#include "Lights.h"
#include "RenderingEngine.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"

void BaseLight::AddToRenderingEngine(RenderingEngine* renderingEngine) 
{
	renderingEngine->AddLight(this);
}

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity,  glm::vec3 direction) :
BaseLight(color, intensity),
direction(glm::normalize(direction))
{
	SetShader(ForwardDirectional::GetInstance());
}

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation atten, glm::vec3 position, float range) :
BaseLight(color, intensity),
atten(atten),
position(position),
range(range)
{
	SetShader(ForwardPoint::GetInstance());
}