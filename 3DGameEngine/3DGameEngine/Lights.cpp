#include "Lights.h"
#include "renderingEngine.h"
#include "forwardDirectional.h"
#include "forwardPointLight.h"
#include "forwardSpotLight.h"


namespace 
{
	double maxColor(const glm::vec3& checkMax)
	{
		return glm::max(checkMax.x, glm::max(checkMax.y, checkMax.z));
	}
};

void BaseLight::addToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->addLight(this);
}

DirectionalLight::DirectionalLight() :
m_direction(glm::vec3(0, 0, 0))
{
	m_shader = new ForwardDirectional("forward_Directional");
}

DirectionalLight::DirectionalLight( const glm::vec3& color, const float& intensity, const glm::vec3& direction) :
BaseLight(color, intensity),
m_direction(glm::normalize(direction)) 
{
	m_shader = new ForwardDirectional("forward_Directional");
}

PointLight::PointLight()
{
	m_shader = new ForwardPointLight("forward_PointLight");
}

PointLight::PointLight(const glm::vec3& color, const float& intensity, const Attenuation& atten) :
BaseLight(color, intensity),
m_atten(atten)
{

	//calculate range according to the ability for light to affect color at a distance given a set color depth.
	float a = atten.m_exponent;
	float b = atten.m_linear;
	float c = atten.m_constant - COLOR_DEPTH * m_intensity * maxColor(m_color);

	m_range = (float)(-b + sqrtf(b*b - 4.0 * a*c)) / (2.0 * a); 
	m_shader = new ForwardPointLight("forward_PointLight");
}

SpotLight::SpotLight() :
m_direction(glm::vec3(0, 0, 0)),
m_cutoff(1.0f) 
{
	m_shader = new ForwardSpotLight("forward_SpotLight");
}

SpotLight::SpotLight(const glm::vec3& color, const float& intensity, const Attenuation& atten, const glm::vec3& direction, const float& cutoff) :
PointLight(color, intensity, atten),
m_direction(direction),
m_cutoff(cutoff) 
{
	m_shader = new ForwardSpotLight("forward_SpotLight");
}

