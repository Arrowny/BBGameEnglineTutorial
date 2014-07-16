#include "transform.h"
#include <iostream>
#include "ExtraVecMath.h"

Transform::~Transform()
{
}

glm::mat4 Transform::getTransformation() const
{
	glm::mat4 transMat = glm::translate(m_trans);
	glm::mat4 scaleMat = glm::scale(m_scale);
	//glm::mat4 rotMat = glm::mat4_cast(m_rot);
	glm::mat4 rotMat = glm::mat4(glm::vec4(EXQM::GetRight(m_rot), 0.0), glm::vec4(EXQM::GetUp(m_rot), 0.0), glm::vec4(EXQM::GetForward(m_rot), 0.0), glm::vec4(0.0, 0.0, 0.0, 1.0));

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


