#include "Lights.h"
#include "RenderingEngine.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"

void BaseLight::AddToRenderingEngine(RenderingEngine* renderingEngine) 
{
	renderingEngine->AddLight(this);
}

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity/*,  glm::vec3 direction*/) :
BaseLight(color, intensity)
//direction(glm::normalize(direction))
{
	SetShader(new Shader("./res/shader/fowardDirectional"));
}

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation atten) :
BaseLight(color, intensity),
atten(atten),
position(position),
range(100)
{
	float a = atten.exponent;
	float b = atten.linear;
	float c = atten.constant - COLOR_DEPTH * intensity * glm::max(color.x, glm::max(color.y, color.z));

	range = (float)(-b + std::sqrtf(b*b - 4 * a*c)) / (2 * a);
	SetShader(new Shader("./res/shader/forwardPointLight"));
}

SpotLight::SpotLight(glm::vec3 color, float intensity, const Attenuation atten, float cutoff) :
PointLight(color, intensity, atten),
cutoff(cutoff)
{
	//direction = GetTransform().GetRot().
	SetShader(new Shader("./res/shader/forwardSpotLight"));
}