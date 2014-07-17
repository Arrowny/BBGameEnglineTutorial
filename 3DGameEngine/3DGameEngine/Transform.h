#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Camera.h"
#define PI 3.1415926

class Transform
{
public:

	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(m_pos);
		glm::mat4 scaleMat = glm::scale(m_scale);
		glm::mat4 rotX = glm::rotate(m_rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(m_rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(m_rot.z, glm::vec3(0.0, 0.0, 1.0));
		
		glm::mat4 rotMat = rotZ * rotY * rotX;

		return posMat * rotMat * scaleMat;
	}

	//inline glm::mat4 getProjectedTransformation()
	//{
	//	glm::mat4 transMatrix = GetModel();
	//	glm::mat4 cameraMatrix = Camera::GetViewProjection();
	//}


	//inline glm::vec3* GetPos() { return &m_pos; }
	//inline glm::vec3* GetRot() { return &m_rot; }
	//inline glm::vec3* GetScale() { return &m_scale; }

	//inline void SetPos(glm::vec3& pos) { this->m_pos = pos; }
	//inline void SetRot(glm::vec3& rot) { this->m_rot = rot; }
	//inline void SetScale(glm::vec3& scale) { this->m_scale = scale; }

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }

	inline glm::fvec3 roatate(float angle, glm::fvec3 axis)
	{
		float sinHalfAngle = (float)sin((angle/2)* (PI / 180));
		float cosHalfAngle = (float)cos((angle / 2)* (PI / 180));
		float rx = axis.x * sinHalfAngle;
		float ry = axis.y * sinHalfAngle;
		float rz = axis.z * sinHalfAngle;
		float rw = cosHalfAngle;

		//glm::quat rotation(rx, ry, rz,rw);
	}
	
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;

};

