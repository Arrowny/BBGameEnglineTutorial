#include "spotLight.h"
#include "forwardSpot.h"

spotLight::spotLight(const glm::fvec3& color, float intensity, const Attenuation& atten, float cutoff) :
pointLight(color, intensity, atten),
cutoff(cutoff)
{
	SetShader(ForwardSpot::GetInstance());
}