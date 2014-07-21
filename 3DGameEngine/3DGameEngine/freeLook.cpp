#include "freeLook.h"
#include "renderingEngine.h"
#include "coreEngine.h"

void FreeLook::AddToEngine(coreEngine* engine)
{
	engine->GetRenderingEngine()->AddFreeLook(this);
}