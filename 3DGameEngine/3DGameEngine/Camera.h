#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>


class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);

		glm::normalize(m_up);
		glm::normalize(m_forward);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	inline void move(glm::vec3 dir, float amt)
	{
		m_position = m_position + dir * amt;
	}

	inline void RotateX(float angle)
	{
		glm::vec3 Haxis = glm::cross(glm::vec3(0, 1, 0), m_forward);
		glm::normalize(Haxis);

		m_forward = glm::ro
	}
	inline glm::vec3 GetLeft()
	{
		glm::vec3 left = glm::cross(m_up, m_forward);
		glm::normalize(left);
		return left;
	}

	inline glm::vec3 GetRight()
	{
		glm::vec3 right = glm::cross(m_forward, m_up);
		glm::normalize(right);
		return right;
	}

	inline glm::vec3 GetPos()
	{
		return m_position;
	}

private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;


};

