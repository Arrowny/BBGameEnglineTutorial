#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "gameComponent.h"

struct Camera : public gameComponent
{
public:
	Camera(float fov, float aspect, float zNear, float zFar);

	glm::mat4 GetViewProjection() const;

	virtual void AddToEngine(coreEngine* engine);

protected:
private:
	glm::mat4 projection;
};

