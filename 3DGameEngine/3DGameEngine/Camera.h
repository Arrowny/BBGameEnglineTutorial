#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "gameComponent.h"

struct Camera : public GameComponent
{
public:
	Camera(float fov, float aspect, float zNear, float zFar);

	glm::mat4 GetViewProjection() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetLookAt() const;

	virtual void AddToEngine(CoreEngine* engine);

protected:
private:
	glm::mat4 projection;
};

