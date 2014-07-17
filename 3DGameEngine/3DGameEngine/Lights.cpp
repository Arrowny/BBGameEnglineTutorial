#include "Lights.h"
#include "RenderingEngine.h"

void DirectionalLight::AddToRenderingEngine(RenderingEngine* renderingEngine) 
{
	renderingEngine->AddDirectionalLight(*this);
}

void PointLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->AddPointLight(*this);
}

void SpotLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->AddSpotLight(*this);
}
