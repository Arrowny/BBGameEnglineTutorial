#include "Camera.h"


Camera::Camera(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up)
{

	this->m_pos = pos;
	this->m_forward = forward;
	this->m_up = up;

	glm::normalize(m_up);
	glm::normalize(m_forward);

}

Camera::Camera()
{

	Camera(glm::fvec3(0, 0, 0), glm::fvec3(0, 0, 1), glm::fvec3(0, 1, 0));

}


Camera::~Camera()
{
}

void Camera::move(glm::fvec3 dir, float amt){

	m_pos = m_pos + (dir*amt);

}

glm::fvec3 Camera::getLeft(){

	glm::fvec3 left = glm::cross(m_forward, m_up);
	glm::normalize(left);
	return left;

}

glm::fvec3 Camera::getRight(){

	glm::fvec3 right = glm::cross(m_up, m_forward);
	glm::normalize(right);
	return right;

}

void Camera::rotateX(float angle){

	glm::fvec3 hAxis = glm::cross(yAxis, m_forward);
	glm::normalize(hAxis);

	m_forward = glm::vec3((glm::rotate(angle, hAxis) * glm::fvec4(m_forward, 0.0)));
	glm::normalize(m_forward);

	m_up = glm::cross(m_forward, hAxis);
	glm::normalize(m_up);

}

void Camera::rotateY(float angle){

	glm::fvec3 hAxis = glm::cross(yAxis, m_forward);
	glm::normalize(hAxis);

	m_forward = glm::vec3((glm::rotate(angle, yAxis) * glm::fvec4(m_forward, 0.0)));
	glm::normalize(m_forward);

	m_up = glm::cross(m_forward, hAxis);
	glm::normalize(m_up);

}