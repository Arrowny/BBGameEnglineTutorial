#include "spotLight.h"
#include "Shader.h"

spotLight::spotLight(const glm::fvec3& color, float intensity, const Attenuation& atten, float cutoff) :
pointLight(color, intensity, atten),
cutoff(cutoff)
{
	SetShader(new Shader("./res/forwardSpot"));
}