#include "directionalLight.h"
#include "renderingEngine.h"

void directionalLight::AddToRenderingEngine(renderingEngine* renderingEngine)
{
	renderingEngine->AddDirectionalLight(this);
}