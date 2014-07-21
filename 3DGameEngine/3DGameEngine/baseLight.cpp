#include "baseLight.h"
#include "renderingEngine.h"
#include "coreEngine.h"

void baseLight::AddToEngine(coreEngine* engine)
{
	engine->GetRenderingEngine()->AddLight(this);
}
