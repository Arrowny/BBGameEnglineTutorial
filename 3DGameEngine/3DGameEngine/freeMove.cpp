#include "freeMove.h"
#include "renderingEngine.h"
#include "coreEngine.h"

void FreeMove::AddToEngine(coreEngine* engine)
{
	engine->GetRenderingEngine()->AddFreeMove(this);
}