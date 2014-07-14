#include "pointLight.h"
#include "renderingEngine.h"
#include "forwardPoint.h"

pointLight::pointLight(const glm::fvec3& color, float intensity, const Attenuation& atten, const glm::fvec3& position, float range) :
baseLight(color, intensity),
atten(atten),
position(position),
range(range)
{
	SetShader(ForwardPoint::GetInstance());
}