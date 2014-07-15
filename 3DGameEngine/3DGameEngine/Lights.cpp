#include "Lights.h"
#include "renderingEngine.h"
#include "forwardDirectional.h"
#include "forwardPointLight.h"
#include "forwardSpotLight.h"


void BaseLight::addToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->addLight(this);
}

DirectionalLight::DirectionalLight() :
m_direction(glm::vec3(0, 0, 0))
{
	m_shader = new ForwardDirectional("forward_Directional");
}

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction) :
BaseLight(color, intensity),
m_direction(glm::normalize(direction)) 
{
	m_shader = new ForwardDirectional("forward_Directional");
}

PointLight::PointLight() :
m_position(glm::vec3(0.0, 0.0, 0.0)) 
{
	m_shader = new ForwardPointLight("forward_PointLight");
}

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation atten, glm::vec3 position, float range) :
BaseLight(color, intensity),
m_atten(atten),
m_position(position),
m_range(range) 
{
	m_shader = new ForwardPointLight("forward_PointLight");
}

SpotLight::SpotLight() :
m_direction(glm::vec3(0, 0, 0)),
m_cutoff(1.0f) 
{
	m_shader = new ForwardSpotLight("forward_SpotLight");
}

SpotLight::SpotLight(glm::vec3 color, float intensity, Attenuation atten, glm::vec3 position, float range, glm::vec3 direction, float cutoff) :
PointLight(color, intensity, atten, position, range),
m_direction(direction),
m_cutoff(cutoff) 
{
	m_shader = new ForwardSpotLight("forward_SpotLight");
}