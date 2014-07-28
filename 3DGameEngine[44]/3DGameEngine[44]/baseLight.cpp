#include "baseLight.h"
#include "renderingEngine.h"

void baseLight::AddToRenderingEngine(renderingEngine* renderingEngine)
{
	renderingEngine->AddLight(this);
}
