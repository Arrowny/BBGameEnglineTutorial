#include "camera.h"
#include <iostream>
#include "renderingEngine.h"

Camera::Camera()
{
	totalYRotation = 0.0;
}

Camera::Camera(glm::vec3 pos, glm::vec3 lookAtPoint, glm::vec3 up, double zNear, double zFar, double fov, double screenWidth, double screenHeight)
{
	getTransform()->m_trans = pos;
	m_perspectiveTransform.initPerspectiveMatrix(zNear, zFar, fov, screenWidth, screenHeight);
	lookAt(lookAtPoint, up);
}

void Camera::lookAt(glm::vec3 destPoint, glm::vec3 up)
{
	glm::vec3 forward = findDirectionOfLookAt(destPoint);
	up = calculateTrueUp(up, forward);
	glm::vec3 right = glm::cross(up, forward);

	//nonesense quaternion math
	glm::fquat lookAt;
	lookAt.w = sqrtf(1.0f + right.x + up.y + forward.z) * 0.5f;
	float w4_recip = 1.0f / (4.0f * lookAt.w);
	lookAt.x = (forward.y - up.z) * w4_recip;
	lookAt.y = (right.z - forward.x) * w4_recip;
	lookAt.z = (up.x - right.y) * w4_recip;
	lookAt = glm::normalize(lookAt);

	getTransform()->m_rot = lookAt;
}

Camera::~Camera()
{
}

void Camera::ProcessInput(Input* input, double delta)
{
	float movAmt = 500.0f;
	float rotAmt = 900000.0;

	glm::vec3 center = EXQM::GetForward(getTransform()->m_rot);
	glm::vec3 right = EXQM::GetRight(getTransform()->m_rot);
	glm::vec3 left = EXQM::GetLeft(getTransform()->m_rot);

	glm::vec3 yAxis( 0.0, 1.0, 0);
	glm::vec3 xAxis = right;


	if (input->GetKeyDown(Input::KEY_W))
	{
		getTransform()->translate(center, movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_S))
	{
		getTransform()->translate(center, -movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_D))
	{
		getTransform()->translate(left, movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_A))
	{
		getTransform()->translate(right, movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_UP))
	{
			getTransform()->rotate(-rotAmt*delta, xAxis);
	}

	if (input->GetKeyDown(Input::KEY_DOWN))
	{
		getTransform()->rotate(rotAmt*delta, xAxis);
	}

	if (input->GetKeyDown(Input::KEY_LEFT))
	{
		getTransform()->rotate(rotAmt*delta, yAxis);
	}

	if (input->GetKeyDown(Input::KEY_RIGHT))
	{
		getTransform()->rotate(-rotAmt*delta, yAxis);
	}

}

void Camera::reinitPerspectiveMatrix(double zNear, double zFar, double fov, double screenWidth, double screenHeight)
{
	m_perspectiveTransform.initPerspectiveMatrix(zNear, zFar, fov, screenWidth, screenHeight);
}

glm::vec3 Camera::findDirectionOfLookAt(glm::vec3 lookAt)
{
	glm::vec3 center(lookAt);
	center = center - getTransform()->m_trans;
	center = glm::normalize(center);
	return center;
}

glm::vec3 Camera::calculateTrueUp(glm::vec3 up, glm::vec3 center)
{
	glm::vec3 projection(center);

	double magnitude = glm::dot(up, center);
	if (magnitude == 0.0f)
	{
		center.y += .001f; center.x += .001f; center.z += .001;
	}

	projection *= magnitude;

	glm::vec3 trueUp = glm::normalize(up - projection);
	return trueUp;
}

void Camera::addToRenderingEngine(RenderingEngine* renderingEngine)
{
	renderingEngine->addCamera(this);
}




