#include "transform.h"
#include <iostream>

Transform::~Transform()
{
}

glm::mat4 Transform::getTransformation() const
{
	glm::mat4 transMat = glm::translate(m_trans);
	glm::mat4 scaleMat = glm::scale(m_scale);

	glm::mat4 rotXMat = glm::rotate(m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotYMat = glm::rotate(m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotZMat = glm::rotate(m_rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotMat = rotZMat * rotYMat * rotXMat; //TODO: use quaternions to generate rotation matrix

	return transMat * rotMat * scaleMat;
}

glm::mat4 Transform::getPerspectiveMatrix()
{
	if (perspectiveInitialized)
	{ 
		return glm::mat4(glm::perspective(fov, aspect, zNear, zFar)); 
	}
	else
	{
		std::cerr << "Error: Perspective matrix not initialized" << std::endl;
		exit(1);
	}
}

glm::mat4 Transform::getOrthogonalMatrix(float left, float right, float top, float bottom, float near, float far)
{
	return glm::ortho(left, right, bottom, top, near, far);
}

void Transform::initPerspectiveMatrix(const double& zNear, const double& zFar, const double& fov, const double& screenWidth, const double& screenHeight)
{
	perspectiveInitialized = true;
	this->zNear = zNear;
	this->zFar = zFar;
	this->fov = fov;
	aspect = screenWidth / screenHeight;
}


