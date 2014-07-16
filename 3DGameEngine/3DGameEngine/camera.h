#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "transform.h"
#include "Input.h"
#include "ExtraVecMath.h"
#include "gameComponent.h"

class RenderingEngine;

class Camera : 
	public GameComponent
{
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 lookAtPoint, glm::vec3 up, double zNear, double zFar, double fov, double screenWidth, double screenHeight);
	virtual ~Camera();

	virtual void ProcessInput(Input* input, double delta);
	virtual void addToRenderingEngine(RenderingEngine* renderingEngine);

	void reinitPerspectiveMatrix(double zNear, double zFar, double fov, double screenWidth, double screenHeight);
	void Camera::lookAt(glm::vec3 destPoint, glm::vec3 up)
	//void lookAt(const glm::vec3& lookAt, const glm::vec3& up);
	void move(const glm::vec3& dir, const float& amt);

	glm::mat4 getPerspectiveTransform() { return m_perspectiveTransform.getPerspectiveMatrix(); }
	glm::mat4 getCameraTransform() { return getTransform()->getLookAt(); }
	glm::mat4 getProjectionTransform() { return m_perspectiveTransform.getPerspectiveMatrix() * getCameraTransform(); }
	
private:

	glm::vec3 findDirectionOfLookAt(glm::vec3 lookAt);
	glm::vec3 calculateTrueUp(glm::vec3 up, glm::vec3 center);

	Transform m_perspectiveTransform;
	float totalYRotation;
};

