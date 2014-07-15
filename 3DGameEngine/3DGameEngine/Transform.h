#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

struct Transform
{
public:

	Transform(const glm::vec3& pos = glm::vec3(), const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(m_pos);
		glm::mat4 scaleMat = glm::scale(m_scale);
		glm::mat4 rotMat = glm::mat4_cast(m_rot);

		return posMat * rotMat * scaleMat;
	}

	/*inline glm::vec3 GetCameraPos(const Camera& camera) const
	{
		return camera.getPos();
	}*/

	/*inline glm::mat4 GetProjection(const Camera& camera) const
	{
		glm::mat4 VP = camera.GetViewProjection();
		glm::mat4 M = GetModel();

		return VP * M;
	}*/

	inline glm::vec3& GetPos() { return m_pos; }
	inline const glm::fvec3& GetPos() const { return m_pos; }
	inline glm::quat& GetRot() { return m_rot; }
	inline const glm::quat& GetRot() const { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::quat& rot) { m_rot = rot; }
	inline void SetScale(glm::vec3& scale) { m_scale = scale; }

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

protected:
private:
	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;
	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;

};

#endif