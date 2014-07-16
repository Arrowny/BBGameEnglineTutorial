#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\vector_query.hpp>

struct Transform
{
public:

	Transform(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_parent(0),
		m_parentMat(glm::mat4())
		{}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(m_pos);
		glm::mat4 scaleMat = glm::scale(m_scale);
		glm::mat4 rotMat = glm::mat4_cast(m_rot);

		if (m_parent != 0 && m_parent->HasChanged())
		{
			m_parentMat = m_parent->GetModel();
		}

		if (!glm::isNull(m_oldPos, 0.0001f))
		{
			m_oldPos = m_pos;
			m_oldRot = m_rot;
			m_oldScale = m_scale;
		}
		
		return m_parentMat * posMat * rotMat * scaleMat;
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline const glm::fvec3& GetPos() const { return m_pos; }
	inline glm::quat& GetRot() { return m_rot; }
	inline const glm::quat& GetRot() const { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::quat& rot) { m_rot = rot; }
	inline void SetScale(glm::vec3& scale) { m_scale = scale; }
	inline void SetParent(Transform* parent) { m_parent = parent; }

	inline glm::fvec3 GetForward() const
	{
		return glm::fvec3(2.0f * (m_rot.x * m_rot.z - m_rot.w * m_rot.y), 
						  2.0f * (m_rot.y * m_rot.z + m_rot.w * m_rot.x), 
						  1.0f - 2.0f * (m_rot.x * m_rot.x + m_rot.y * m_rot.y));
	}

	inline glm::fvec3 GetLeft() const
	{
		return glm::fvec3(-(1.0f - 2.0f * (m_rot.y*m_rot.y + m_rot.z*m_rot.z)), 
						  -2.0f * (m_rot.x*m_rot.y - m_rot.w*m_rot.z), 
						  -2.0f * (m_rot.x*m_rot.z + m_rot.w*m_rot.y));
	}

	inline glm::fvec3 GetRight() const
	{
		return glm::fvec3(1.0f - 2.0f * (m_rot.y*m_rot.y + m_rot.z*m_rot.z), 
						  2.0f * (m_rot.x*m_rot.y - m_rot.w*m_rot.z), 
						  2.0f * (m_rot.x*m_rot.z + m_rot.w*m_rot.y));
	}

	inline glm::fvec3 GetUp() const
	{
		return glm::fvec3(2.0f * (m_rot.x*m_rot.y + m_rot.w*m_rot.z), 
						  1.0f - 2.0f * (m_rot.x*m_rot.x + m_rot.z*m_rot.z), 
						  2.0f * (m_rot.y*m_rot.z - m_rot.w*m_rot.x));
	}

	inline glm::quat initRotation(const glm::fvec3& axis, float angle)
	{
		float sinHalfAngle = sinf(angle / 2.0f);
		float cosHalfAngle = cosf(angle / 2.0f);

		m_rot.x = axis.x * sinHalfAngle;
		m_rot.y = axis.y * sinHalfAngle;
		m_rot.z = axis.z * sinHalfAngle;
		m_rot.w = cosHalfAngle;

		return m_rot;
	}

	inline bool Transform::HasChanged()
	{

		if (glm::isNull(m_oldPos, 0.0001f))
		{
			m_oldPos = glm::vec3(0, 0, 0);
			m_oldRot = glm::quat(0, 0, 0, 0);
			m_oldScale = glm::vec3(0, 0, 0);

			return true;
		}

		if (m_parent != 0 && m_parent->HasChanged())
		{
			return true;
		}

		if (m_pos != m_oldPos)
		{
			return true;
		}

		if (m_rot != m_oldRot)
		{
			return true;
		}
			
		if (m_scale != m_scale)
		{
			return true;
		}
			
		return false;
	}

protected:
private:
	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;
	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;

	Transform* m_parent;
	mutable glm::mat4 m_parentMat;
	mutable glm::vec3 m_oldPos;
	mutable glm::quat m_oldRot;
	mutable glm::vec3 m_oldScale;

};

#endif