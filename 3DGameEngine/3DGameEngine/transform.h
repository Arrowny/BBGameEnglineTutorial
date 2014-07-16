#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "ExtraVecMath.h"

class Transform
{
public:
	Transform() :
		m_trans(glm::vec3(0.0, 0.0, 0.0)),
		m_rot(glm::quat(1.0, 0.0, 0.0, 0.0)),
		m_scale(glm::vec3(1.0, 1.0, 1.0)) {}

	Transform(const glm::vec3& translation, const glm::quat& rotation = glm::quat(1.0, 0.0, 0.0, 0.0), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_trans(translation),
		m_rot(rotation),
		m_scale(scale) {}

	virtual ~Transform();

	inline void setTranslationExplicit(float x, float y, float z) { this->m_trans.x = x; this->m_trans.y = y; this->m_trans.z = z;	}
	inline void translate(glm::vec3 direction, float amt) { m_trans += (direction*amt); }
	inline void setRotationExplicit(float degreeRotation, glm::vec3 axis){ m_rot = glm::angleAxis(degreeRotation, axis); }
	inline void rotate(float degreeRotation, glm::vec3 axis) { m_rot = glm::normalize(m_rot*glm::angleAxis(glm::radians(degreeRotation), axis)); }
	inline void setScaleExplicit(float sx, float sy, float sz) {	this->m_scale.x = sx; this->m_scale.y = sy; this->m_scale.z = sz;	}

	glm::mat4 getTransformation() const;
	glm::mat4 getPerspectiveMatrix();
	glm::mat4 getOrthogonalMatrix(float left, float right, float top, float bottom, float near, float far);
	glm::mat4 getLookAt() { return glm::lookAt(m_trans, m_trans + EXQM::GetForward(m_rot), EXQM::GetUp(m_rot)); }
	void initPerspectiveMatrix(const double& zNear, const double& zFar, const double& fov, const double& screenWidth, const double& screenHeight);
		
	glm::vec3 m_trans;
	glm::quat m_rot;
	glm::vec3 m_scale;
private:
	double zNear;
	double zFar;
	double fov;
	double aspect;

	bool perspectiveInitialized = false;
};

