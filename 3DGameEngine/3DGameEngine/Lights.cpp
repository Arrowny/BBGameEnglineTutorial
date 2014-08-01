#include "Lights.h"
#include "renderingEngine.h"
#include "coreEngine.h"
#include "Shader.h"

#define COLOR_DEPTH 256

void BaseLight::AddToEngine(CoreEngine* engine)
{
	engine->GetRenderingEngine()->AddLight(this);
}

DirectionalLight::DirectionalLight(const glm::fvec3& color, float intensity) :
BaseLight(color, intensity),
direction(glm::normalize(direction))
{
	SetShader(new Shader("forwardDirectional"));
}

PointLight::PointLight(const glm::fvec3& color, float intensity, const Attenuation& atten) :
BaseLight(color, intensity),
atten(atten)
{
	float a = atten.m_exponent;
	float b = atten.m_linear;
	float c = atten.m_constant - COLOR_DEPTH * intensity * glm::max(color.x, glm::max(color.y, color.z));

	range = (float)((-b + sqrtf(b*b - 4.0f * a*c)) / (2.0f * a));

	SetShader(new Shader("forwardPoint"));;
}

SpotLight::SpotLight(const glm::fvec3& color, float intensity, const Attenuation& atten, float cutoff) :
PointLight(color, intensity, atten),
cutoff(cutoff)
{
	SetShader(new Shader("forwardSpot"));
}