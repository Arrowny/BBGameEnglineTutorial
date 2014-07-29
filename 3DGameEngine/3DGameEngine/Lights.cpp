#include "Lights.h"
#include "renderingEngine.h"
#include "coreEngine.h"
#include "Shader.h"

#define COLOR_DEPTH 256

void baseLight::AddToEngine(coreEngine* engine)
{
	engine->GetRenderingEngine()->AddLight(this);
}

directionalLight::directionalLight(const glm::fvec3& color, float intensity) :
baseLight(color, intensity),
direction(glm::normalize(direction))
{
	SetShader(new Shader("./res/forwardDirectional"));
}

pointLight::pointLight(const glm::fvec3& color, float intensity, const Attenuation& atten) :
baseLight(color, intensity),
atten(atten)
{
	float a = atten.m_exponent;
	float b = atten.m_linear;
	float c = atten.m_constant - COLOR_DEPTH * intensity * glm::max(color.x, glm::max(color.y, color.z));

	range = (float)((-b + sqrtf(b*b - 4.0f * a*c)) / (2.0f * a));

	SetShader(new Shader("./res/forwardPoint"));;
}

spotLight::spotLight(const glm::fvec3& color, float intensity, const Attenuation& atten, float cutoff) :
pointLight(color, intensity, atten),
cutoff(cutoff)
{
	SetShader(new Shader("./res/forwardSpot"));
}