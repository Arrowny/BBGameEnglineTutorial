#include "camera.h"
#include <iostream>

Camera::Camera()
{
	m_pos = glm::vec3(0.0, 0.0, 0.0);
	m_center = glm::vec3(0.0, 0.0, 1.0);
	m_up = glm::vec3(0.0, 1.0, 0.0);
}

Camera::Camera(glm::vec3 pos, glm::vec3 lookAtPoint, glm::vec3 up, double zNear, double zFar, double fov, double screenWidth, double screenHeight)
{
	this->m_pos = pos;
	m_perspectiveTransform.initPerspectiveMatrix(zNear, zFar, fov, screenWidth, screenHeight);
	lookAt(lookAtPoint, up);
}


void Camera::lookAt(const glm::vec3& lookAt, const glm::vec3& up)
{
	this->m_center = findDirectionOfLookAt(lookAt);
	this->m_up = calculateTrueUp(up, m_center);
}

Camera::~Camera()
{
}

void Camera::input(const Input& input)
{
	float movAmt = 500.0f;
	float rotAmt = 20000.0;

	if (input.GetKeyDown(Input::KEY_W))
	{
		move(m_center, movAmt*Time::DELTA);
	}

	if (input.GetKeyDown(Input::KEY_S))
	{
		move(m_center, -movAmt*Time::DELTA);
	}

	if (input.GetKeyDown(Input::KEY_A))
	{
		move(getLeft(), movAmt*Time::DELTA);
	}

	if (input.GetKeyDown(Input::KEY_D))
	{
		move(getRight(), movAmt*Time::DELTA);
	}

	if (input.GetKeyDown(Input::KEY_UP))
	{
		rotateX(-rotAmt*Time::DELTA);
	}

	if (input.GetKeyDown(Input::KEY_DOWN))
	{
		rotateX(rotAmt*Time::DELTA);
	}

	if (input.GetKeyDown(Input::KEY_LEFT))
	{
		rotateY(rotAmt*Time::DELTA);
	}

	if (input.GetKeyDown(Input::KEY_RIGHT))
	{
		rotateY(-rotAmt*Time::DELTA);
	}

}

void Camera::reinitPerspectiveMatrix(double zNear, double zFar, double fov, double screenWidth, double screenHeight)
{
	m_perspectiveTransform.initPerspectiveMatrix(zNear, zFar, fov, screenWidth, screenHeight);
}

void Camera::move(const glm::vec3& dir, const float& amt)
{
	m_pos += (dir*amt);
}

void Camera::rotateX(float angle)
{
	glm::vec3 yAxis(0.0, 1.0, 0.0);
	glm::vec3 hAxis = glm::cross(yAxis, m_center);
	hAxis = glm::normalize(hAxis);

	m_center = glm::vec3(glm::rotate(angle, hAxis)*glm::vec4(m_center, 1.0));
	m_center = glm::normalize(m_center);

	m_up = glm::normalize(glm::cross(m_center, hAxis));
}

void Camera::rotateY(float angle)
{
	glm::vec3 yAxis(0.0, 1.0, 0.0);
	glm::vec3 hAxis = glm::cross(yAxis, m_center);
	hAxis = glm::normalize(hAxis);

	m_center = glm::vec3(glm::rotate(angle, yAxis)*glm::vec4(m_center, 1.0));
	m_center = glm::normalize(m_center);

	m_up = glm::normalize(glm::cross(m_center, hAxis));
}

glm::vec3 Camera::getLeft()
{
	return glm::normalize(glm::cross(m_up, m_center));
}

glm::vec3 Camera::getRight()
{
	return glm::normalize(glm::cross(m_center, m_up));
}

glm::vec3 Camera::findDirectionOfLookAt(glm::vec3 lookAt)
{
	glm::vec3 center(lookAt);
	center = center - m_pos;
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




