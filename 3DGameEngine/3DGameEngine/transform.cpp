#include "transform.h"
#include <iostream>


Transform::Transform() :
m_trans(glm::vec3(0.0, 0.0, 0.0)),
m_rot(glm::quat(1.0, 0.0, 0.0, 0.0)),
m_scale(glm::vec3(1.0, 1.0, 1.0)),
parent(NULL),
parentMatrix(glm::mat4(1.0)),
oldTrans(NULL),
oldRot(NULL),
oldScale(NULL) 
{
}

Transform::Transform(const glm::vec3& translation, const glm::fquat& rotation, const glm::vec3& scale) :
m_trans(translation),
m_rot(rotation),
m_scale(scale),
parent(NULL),
parentMatrix(glm::mat4(1.0)),
oldTrans(NULL),
oldRot(NULL),
oldScale(NULL)
{
}

Transform::~Transform()
{
}

void Transform::UpdateTRS()
{
	
	if (oldTrans != NULL)
	{
		if (hasChanged())
		{
			chkChanged = true;
		}

		*oldTrans = m_trans;
		*oldRot = m_rot;
		*oldScale = m_scale;
	}
	else
	{
		//set values to insure that oldTRS are not equal the first time through.
		oldTrans = new glm::vec3(m_trans.x + .5, m_trans.y + .5, m_trans.z + .5);
		oldRot = new glm::quat(m_rot.w + .5, m_rot.x + .5, m_rot.y + .5, m_rot.z + .5);
		oldScale = new glm::vec3(m_scale.x + .5, m_scale.y + .5, m_scale.z + .5);
	}
}

bool Transform::hasChanged()
{
	if (chkChanged)
	{
		return true;
	}

	if ( (parent != NULL) && parent->hasChanged()) 
	{ 
		return true; 
	}
	if (m_trans != *oldTrans || m_rot != *oldRot || m_scale != *oldScale) 
	{ 
		return true; 
	}

	return false;
}

glm::mat4 Transform::getParentMatrix()
{
	//if (parent != NULL && parent->hasChanged())
	//{
	//	chkChanged = false;
	//	parentMatrix = parent->getTransformation();
	//}

	if (parent != NULL)
	{
		parentMatrix = parent->getTransformation();
	}
		
	return parentMatrix;
}

glm::mat4 Transform::getTransformation()
{
	glm::mat4 transMat = glm::translate(m_trans);
	glm::mat4 scaleMat = glm::scale(m_scale);
	glm::mat4 rotMat = glm::mat4_cast(m_rot);

	return  getParentMatrix() * transMat * rotMat * scaleMat;
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

glm::mat4 Transform::getLookAt() 
{ 
	//return glm::lookAt( getTransformedTrans(), 
	//					getTransformedTrans() + EXQM::GetForward(getTransformedRot()), 
	//					EXQM::GetUp(getTransformedRot()));

	return glm::lookAt( m_trans, 
						m_trans + EXQM::GetForward(m_rot),
						EXQM::GetUp(m_rot));
}

void Transform::initPerspectiveMatrix(const double& zNear, const double& zFar, const double& fov, const double& screenWidth, const double& screenHeight)
{
	perspectiveInitialized = true;
	this->zNear = zNear;
	this->zFar = zFar;
	this->fov = fov;
	aspect = screenWidth / screenHeight;
}

glm::vec3 Transform::getTransformedTrans()
{
	glm::mat4 p = getParentMatrix();
	glm::vec3 t = m_trans;
	glm::vec3 transformedTrans( p[0][0] * t.x + p[0][1] * t.y + p[0][2] * t.z + p[0][3],
								p[1][0] * t.x + p[1][1] * t.y + p[1][2] * t.z + p[1][3],
								p[2][0] * t.x + p[2][1] * t.y + p[2][2] * t.z + p[2][3]);

	//glm::vec3 transformedTrans = glm::vec3(getParentMatrix()*glm::vec4(m_trans, 1.0f));
	return transformedTrans;
}

glm::fquat Transform::getTransformedRot()
{
	glm::fquat parentQuat = glm::quat(1, 0, 0, 0);

	if (parent != NULL)
	{
		parentQuat = parent->getTransformedRot();
	}

	return   glm::normalize(glm::cross(parentQuat, m_rot));
}


