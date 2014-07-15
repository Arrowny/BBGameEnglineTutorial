#include "Camera.h"
#include "renderingEngine.h"

void Camera::AddToRenderingEngine(renderingEngine* renderingEngine)
{
	renderingEngine->AddCamera(this);
}