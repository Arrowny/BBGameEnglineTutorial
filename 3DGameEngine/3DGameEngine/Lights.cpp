#include "Lights.h"
#include "renderingEngine.h"
#include "coreEngine.h"
#include "shader.h"
#include "ExtraVecMath.h"

namespace
{
	double maxColor(const glm::vec3& checkMax)
	{
		return glm::max(checkMax.x, glm::max(checkMax.y, checkMax.z));
	}
};

void BaseLight::addToEngine(CoreEngine* coreEngine)
{
	coreEngine->m_renderingEngine.addLight(this);
}

DirectionalLight::DirectionalLight()
{
	m_shader = new Shader("forward_Directional");
}

DirectionalLight::DirectionalLight(const glm::vec3& color, const float& intensity) :
BaseLight(color, intensity)
{
	m_shader = new Shader("forward_Directional");
}

glm::vec3 DirectionalLight::getDirection() { return EXQM::GetForward(getTransform()->m_rot); }

PointLight::PointLight()
{
	m_shader = new Shader("forward_PointLight");
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
	m_shader = new Shader("forward_PointLight");
}

SpotLight::SpotLight() :
m_cutoff(1.0f)
{
	m_shader = new Shader("forward_SpotLight");
}

SpotLight::SpotLight(const glm::vec3& color, const float& intensity, const Attenuation& atten, const float& cutoff) :
PointLight(color, intensity, atten),
m_cutoff(cutoff)
{
	m_shader = new Shader("forward_SpotLight");
}

glm::vec3 SpotLight::getDirection() { return EXQM::GetForward(getTransform()->m_rot); }

