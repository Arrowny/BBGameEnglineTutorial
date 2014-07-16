#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\vector_query.hpp>
#include <glm\gtx\rotate_vector.hpp>

struct Transform
{
public:

	Transform(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::normalize(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_parent(0),
		m_parentMat(glm::mat4()),
		m_initializedOld(false)
		{}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(m_pos);
		glm::mat4 scaleMat = glm::scale(m_scale);
		glm::mat4 rotMat = glm::mat4_cast(m_rot);

		/*if (m_initializedOld)
		{
			m_oldPos = m_pos;
			m_oldRot = m_rot;
			m_oldScale = m_scale;
		}
		*/
		return GetParentMatrix() * posMat * rotMat * scaleMat;
	}

	inline bool HasChanged()
	{

		/*if (!m_initializedOld)
		{
		m_oldPos = m_pos;
		m_oldRot = m_rot;
		m_oldScale = m_scale;
		m_initializedOld = true;

		return true;
		}
		*/
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

	inline void Update()
	{
		if (m_initializedOld)
		{
			m_oldPos = m_pos;
			m_oldRot = -m_rot;
			m_oldScale = m_scale;
		}
		else
		{
			m_oldPos = m_pos + glm::fvec3(1.0f, 1.0f, 1.0f);
			m_oldRot = m_rot * 0.5f;
			m_oldScale = glm::vec3(m_scale.x + 1.0f, m_scale.y + 1.0f, m_scale.z + 1.0f);
			m_initializedOld = true;
		}
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

	inline glm::vec3 GetTransformedPos() const
	{
		glm::vec4 transPos(m_pos, 1.0);

		return glm::vec3(GetParentMatrix() * transPos);

	}

	inline glm::quat GetTransformedRot() const
	{
		glm::quat parentRot = glm::normalize(glm::quat(1, 0, 0, 0));

		if (m_parent != 0)
		{
			parentRot = m_parent->GetTransformedRot();
		}

		return parentRot * m_rot;
	}

	inline glm::fvec3 GetForward() const
	{
		/*glm::quat f_rot = glm::normalize(glm::conjugate(m_rot));

		return glm::fvec3(2.0f * (f_rot.x * f_rot.z - f_rot.w * f_rot.y),
			2.0f * (f_rot.y * f_rot.z + f_rot.w * f_rot.x),
			1.0f - 2.0f * (f_rot.x * f_rot.x + f_rot.y * f_rot.y));*/

		return glm::fvec3(2.0f * (m_rot.x * m_rot.z - m_rot.w * m_rot.y),
			2.0f * (m_rot.y * m_rot.z + m_rot.w * m_rot.x),
			1.0f - 2.0f * (m_rot.x * m_rot.x + m_rot.y * m_rot.y));

		/*return glm::rotate(m_rot, glm::vec3(1, 0, 0));*/
	}

	inline glm::fvec3 GetLeft() const
	{
		/*glm::quat l_rot = GetTransformedRot();

		return glm::fvec3(-(1.0f - 2.0f * (l_rot.y*l_rot.y + l_rot.z*l_rot.z)),
			-2.0f * (l_rot.x*l_rot.y - l_rot.w*l_rot.z),
			-2.0f * (l_rot.x*l_rot.z + l_rot.w*l_rot.y));*/

		return glm::fvec3(-(1.0f - 2.0f * (m_rot.y*m_rot.y + m_rot.z*m_rot.z)),
			-2.0f * (m_rot.x*m_rot.y - m_rot.w*m_rot.z),
			-2.0f * (m_rot.x*m_rot.z + m_rot.w*m_rot.y));

		/*return glm::rotate(m_rot, glm::vec3(-1,0,0));*/
	}

	inline glm::fvec3 GetRight() const
	{
		/*glm::quat r_rot = glm::normalize(glm::conjugate(m_rot));

		return glm::fvec3(1.0f - 2.0f * (r_rot.y*r_rot.y + r_rot.z*r_rot.z),
						  2.0f * (r_rot.x*r_rot.y - r_rot.w*r_rot.z),
						  2.0f * (r_rot.x*r_rot.z + r_rot.w*r_rot.y));*/

		return glm::fvec3(1.0f - 2.0f * (m_rot.y*m_rot.y + m_rot.z*m_rot.z),
						  2.0f * (m_rot.x*m_rot.y - m_rot.w*m_rot.z),
						  2.0f * (m_rot.x*m_rot.z + m_rot.w*m_rot.y));

		/*return glm::rotate(m_rot, glm::vec3(1, 0, 0));*/
	}

	inline glm::fvec3 GetUp() const
	{
		/*glm::quat u_rot = GetTransformedRot();

		return glm::fvec3(2.0f * (u_rot.x*u_rot.y + u_rot.w*u_rot.z),
			1.0f - 2.0f * (u_rot.x*u_rot.x + u_rot.z*u_rot.z),
			2.0f * (u_rot.y*u_rot.z - u_rot.w*u_rot.x));*/

		return glm::fvec3(2.0f * (m_rot.x*m_rot.y + m_rot.w*m_rot.z),
			1.0f - 2.0f * (m_rot.x*m_rot.x + m_rot.z*m_rot.z),
			2.0f * (m_rot.y*m_rot.z - m_rot.w*m_rot.x));

		/*return glm::rotate(m_rot, glm::vec3(0, 1, 0));*/
	}

	//inline glm::fvec3 Rotate(const glm::quat& rotation) const
	//{
	//glm::quat conjugateQ = glm::conjugate(rotation);
	//glm::quat w = rotation * (const glm::fvec3) * conjugateQ;

	//glm::fvec3 ret(w.x, w.y, w.z);

	//return ret;
	//}

protected:
private:

	inline glm::mat4 Transform::GetParentMatrix() const
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
	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;

	Transform* m_parent;
	mutable glm::mat4 m_parentMat;
	mutable glm::vec3 m_oldPos;
	mutable glm::quat m_oldRot;
	mutable glm::vec3 m_oldScale;
	bool m_initializedOld;

};

#endif