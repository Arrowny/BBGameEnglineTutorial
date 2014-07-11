#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
class Transform
{
public:
	Transform() :
		m_trans(glm::vec3(0.0,0.0,0.0)),
		m_rot(glm::vec3(0.0, 0.0, 0.0)),
		m_scale(glm::vec3(1.0, 1.0, 1.0)) {}

	Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_trans(translation),
		m_rot(rotation),
		m_scale(scale) {}

	virtual ~Transform();

	inline void setTranslationExplicit(float x, float y, float z) { this->m_trans.x = x;
																	this->m_trans.y = y;
																	this->m_trans.z = z;	}

	inline void setRotationExplicit(float rx, float ry, float rz){	this->m_rot.x = rx;
																	this->m_rot.y = ry;
																	this->m_rot.z = rz;		}

	inline void setScaleExplicit(float sx, float sy, float sz) {	this->m_scale.x = sx;
																	this->m_scale.y = sy;
																	this->m_scale.z = sz;	}

	glm::mat4 getTransformation() const;
	glm::mat4 getPerspectiveMatrix();
	void initPerspectiveMatrix(const double& zNear, const double& zFar, const double& fov, const double& screenWidth, const double& screenHeight);
		
	glm::vec3 m_trans;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
private:

	double zNear;
	double zFar;
	double fov;
	double aspect;

	bool perspectiveInitialized = false;
};

