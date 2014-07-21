#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\vector_query.hpp>
#include <glm\gtx\rotate_vector.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_parent(0),
		m_parentMat(glm::mat4()),
		oldExist(false) {}

	inline glm::mat4 GetModel()
	{
		glm::mat4 posMat = glm::translate(m_pos);
		glm::mat4 scaleMat = glm::scale(m_scale);
		glm::mat4 rotX = glm::rotate(m_rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(m_rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(m_rot.z, glm::vec3(0.0, 0.0, 1.0));

		glm::mat4 rotMat = rotZ * rotY * rotX;

		if (oldExist)
		{
			m_oldpos = m_pos;
			m_oldrot = m_rot;
			m_oldscale = m_scale;
		}
		return GetParentMatrix() * posMat * rotMat * scaleMat;
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::quat& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::quat& rot) { m_rot = rot; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }


	//inline void Update()
	//{
	//	if (oldExist)
	//	{
	//		m_oldpos = m_pos;
	//		m_oldrot = m_rot;
	//		m_oldscale = m_scale;
	//	}
	//	else
	//	{
	//		m_oldpos = m_pos + glm::fvec3(1, 1, 1);
	//		m_oldrot = m_rot * 0.5f;
	//		m_oldscale = m_scale + glm::vec3(1, 1, 1);
	//		oldExist = true;
	//	}
	//}

	//inline glm::vec3 GetTransformedPos()
	//{
	//	glm::vec4 transPos(m_pos, 1.0);

	//	return glm::vec3(GetParentMatrix() * transPos);

	//}

	//inline glm::quat GetTransformedRot()
	//{
	//	glm::quat parentRot = glm::normalize(glm::quat(1, 0, 0, 0));

	//	if (m_parent != 0)
	//	{
	//		parentRot = m_parent->GetTransformedRot();
	//	}

	//	return parentRot * m_rot;
	//}

	inline bool Transform::HasChanged()
	{

		if (!oldExist)
		{
			m_oldpos = m_pos;
			m_oldrot = m_rot;
			m_oldscale = m_scale;
			oldExist = true;

			return true;
		}

		if (m_parent != 0 && m_parent->HasChanged())
			return true;

		if (m_pos != m_oldpos)
			return true;

		if (m_rot != m_oldrot)
			return true;

		if (m_scale != m_oldscale)
			return true;

		return false;
	}
private:
	inline glm::mat4 Transform::GetParentMatrix()
	{
		if (m_parent != 0 && m_parent->HasChanged())
		{
			m_parentMat = m_parent->GetModel();
		}

		return m_parentMat;
	}
	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;

	Transform* m_parent;
	glm::mat4 m_parentMat;
	glm::vec3 m_oldpos;
	glm::quat m_oldrot;
	glm::vec3 m_oldscale;
	bool oldExist;
};

