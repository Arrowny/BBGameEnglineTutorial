#include "Camera.h"
#include "RenderingEngine.h"

void Camera::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->AddCamera(this);
}