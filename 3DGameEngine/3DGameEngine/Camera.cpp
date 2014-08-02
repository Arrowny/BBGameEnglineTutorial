#include "Camera.h"
#include "renderingEngine.h"
#include "coreEngine.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	this->projection = glm::perspective(fov, aspect, zNear, zFar);
}

glm::mat4 Camera::GetViewProjection() const
{
	return projection * glm::lookAt(GetTransform().GetTransformedPos(), GetTransform().GetTransformedPos() + GetTransform().GetForward(), GetTransform().GetUp());
}

glm::mat4 Camera::GetPerspective() const
{
	return projection;
}

void Camera::AddToEngine(CoreEngine* engine)
{
	engine->GetRenderingEngine()->AddCamera(this);
}