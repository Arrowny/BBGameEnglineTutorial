#include "pointLight.h"
#include "renderingEngine.h"

void pointLight::AddToRenderingEngine(renderingEngine* renderingEngine)
{
	renderingEngine->AddPointLight(this);
}