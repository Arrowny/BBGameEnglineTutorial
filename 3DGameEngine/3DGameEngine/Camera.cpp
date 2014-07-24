#include "Camera.h"
#include "coreEngine.h"

void Camera::AddToEngine(coreEngine* engine)
{
	engine->GetRenderingEngine()->AddCamera(this);
}