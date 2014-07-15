#include "pointLight.h"
#include "renderingEngine.h"
#include "forwardPoint.h"
#include <glm/gtx/extented_min_max.hpp>

#define COLOR_DEPTH 256

pointLight::pointLight(const glm::fvec3& color, float intensity, const Attenuation& atten) :
baseLight(color, intensity),
atten(atten)
{
	float a = atten.m_exponent;
	float b = atten.m_linear;
	float c = atten.m_constant - COLOR_DEPTH * intensity * glm::max(color.x, glm::max(color.y, color.z));

	range = (float)((-b + sqrtf(b*b - 4 * a*c)) / (2 * a));

	SetShader(ForwardPoint::GetInstance());
}