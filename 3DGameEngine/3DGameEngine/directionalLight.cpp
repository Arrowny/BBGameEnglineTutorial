#include "directionalLight.h"
#include "renderingEngine.h"
#include "forwardDirectional.h"

directionalLight::directionalLight(const glm::fvec3& color, float intensity):
baseLight(color, intensity),
direction(glm::normalize(direction))
{
	SetShader(ForwardDirectional::GetInstance());
}
