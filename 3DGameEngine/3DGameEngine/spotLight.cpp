#include "spotLight.h"
#include "forwardSpot.h"

spotLight::spotLight(const glm::fvec3& color, float intensity, const Attenuation& atten, const glm::fvec3& direction, float cutoff) :
pointLight(color, intensity, atten),
direction(direction),
cutoff(cutoff)
{
	SetShader(ForwardSpot::GetInstance());
}