#include "Lights.h"
#include "RenderingEngine.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"

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

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation atten) :
BaseLight(color, intensity),
atten(atten),
position(position),
range(100)
{
	SetShader(ForwardPoint::GetInstance());
}

SpotLight::SpotLight(glm::vec3 color, float intensity, const Attenuation atten,glm::vec3 direction, float cutoff) :
PointLight(color, intensity, atten),
direction(direction),
cutoff(cutoff)
{
	SetShader(ForwardSpot::GetInstance());
}