#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "ExtraVecMath.h"

class Transform
{
public:
	Transform(); 
	Transform(const glm::vec3& translation, const glm::fquat& rotation = glm::quat(1.0, 0.0, 0.0, 0.0), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~Transform();

	inline void translate(glm::vec3 direction, float amt) { m_trans += (direction*amt); }
	inline void rotate(float degreeRotation, glm::vec3 axis) { m_rot = glm::normalize(m_rot*glm::angleAxis(glm::radians(degreeRotation), axis)); }

	inline void setTranslationExplicit(float x, float y, float z) { this->m_trans.x = x; this->m_trans.y = y; this->m_trans.z = z;	}
	inline void setRotationExplicit(float degreeRotation, glm::vec3 axis){ m_rot = m_rot*glm::normalize(glm::angleAxis(degreeRotation, axis)); }
	inline void setScaleExplicit(float sx, float sy, float sz) {	this->m_scale.x = sx; this->m_scale.y = sy; this->m_scale.z = sz;	}
	void setParent(Transform* parent) { this->parent = parent; }

	glm::mat4 getTransformation();
	glm::mat4 getPerspectiveMatrix();
	glm::mat4 getOrthogonalMatrix(float left, float right, float top, float bottom, float near, float far);
	glm::mat4 getLookAt();
	void initPerspectiveMatrix(const double& zNear, const double& zFar, const double& fov, const double& screenWidth, const double& screenHeight);

	glm::vec3 getTransformedTrans();
	glm::fquat getTransformedRot();
	
	void UpdateTRS();
	glm::vec3 m_trans;
	glm::fquat m_rot;
	glm::vec3 m_scale;
private:
	
	bool hasChanged();
	glm::mat4 getParentMatrix(); //convenience method
	glm::vec3* oldTrans;
	glm::fquat* oldRot;
	glm::vec3* oldScale;

	Transform* parent;
	glm::mat4 parentMatrix;

	double zNear;
	double zFar;
	double fov;
	double aspect;

	bool perspectiveInitialized = false;
	bool chkChanged = false;
};

