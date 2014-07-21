#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Timing.h"
#include "Input.h"
#include "Window.h"
#include "gameComponent.h"

struct Camera : public gameComponent
{
public:
	Camera(float fov, float aspect, float zNear, float zFar)
	{
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(GetTransform().GetTransformedPos(), GetTransform().GetTransformedPos() + GetTransform().GetForward(), GetTransform().GetUp());
	}

	virtual void AddToEngine(coreEngine* engine);

protected:
private:
	glm::mat4 projection;
};

