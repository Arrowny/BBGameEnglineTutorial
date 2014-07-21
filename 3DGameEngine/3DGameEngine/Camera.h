#pragma once
//#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include "Input.h"
#include "timing.h"
#include "Window.h"
#include "GameComponent.h"


class Camera :GameComponent
{
public:
	Camera(/*const glm::vec3& pos,*/ float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = glm::vec3(0, 0, 0);
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);

		m_up = glm::normalize(m_up);
		m_forward = glm::normalize(m_forward);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
		
	}

	inline glm::mat4 GetOrthographic(float left, float right, float bottom, float top, float near, float far) const
	{
		return glm::ortho(left, right, bottom, top, near, far);
	}

	bool mouselocked = false;

	glm::vec2 centerPosition = glm::vec2(WindowParameter::width / 2, WindowParameter::height / 2);

	void input(Input input, float delta)
	{
		float snsitivity = 0.1f;

		float movAmt = (float)(10 * delta);
		float rotAmt = (float)(100 * delta);

		if (input.GetKey(input.KEY_ESCAPE))
		{
			input.SetCursor(true);
			mouselocked = false;
		}

		if (mouselocked)
		{
			glm::vec2 deltaPos = glm::vec2(input.GetMousePosition().x - centerPosition.x, input.GetMousePosition().y - centerPosition.y);
			bool rotY = deltaPos.x != 0;
			bool rotX = deltaPos.y != 0;
			if (rotY)
				RotateY(-deltaPos.x * snsitivity);
			if (rotX)
				RotateX(deltaPos.y * snsitivity);
			if (rotX || rotY)
			{
				input.SetMousePosition(glm::vec2(WindowParameter::width / 2, WindowParameter::height / 2));
			}
			//if (SDL_BUTTON_MIDDLE)
			//	sdl_middle

		}


		if (input.GetMouseDown(1))
		{
			input.SetMousePosition(centerPosition);
			input.SetCursor(false);
			mouselocked = true;
		}


		if (input.GetKey(input.KEY_W))
			move(m_forward, movAmt);
		if (input.GetKey(input.KEY_S))
			move(m_forward, -movAmt);
		if (input.GetKey(input.KEY_A))
			move(GetLeft(), movAmt);
		if (input.GetKey(input.KEY_D))
			move(GetRight(), movAmt);

		if (input.GetKey(input.KEY_CAPSLOCK))
			move(m_up, movAmt);
		if (input.GetKey(input.KEY_LSHIFT))
			move(m_up, -movAmt);

		if (input.GetKey(input.KEY_UP))
			RotateX(-rotAmt);
		if (input.GetKey(input.KEY_DOWN))
			RotateX(rotAmt);
		if (input.GetKey(input.KEY_LEFT))
			RotateY(rotAmt);
		if (input.GetKey(input.KEY_RIGHT))
			RotateY(-rotAmt);
	}

	inline void move(glm::fvec3 dir, float amt)
	{
		m_position += (dir * amt);
	}

	inline void RotateX(float angle)
	{
		glm::fvec3 Haxis = glm::cross(yAxis, m_forward);
		Haxis = glm::normalize(Haxis);

		m_forward = glm::rotate(m_forward, angle, Haxis);
		m_forward = glm::normalize(m_forward);

		m_up = glm::cross(m_forward, Haxis);
		m_up = glm::normalize(m_up);
	}

	inline void RotateY(float angle)
	{
		glm::fvec3 Haxis = glm::cross(yAxis, m_forward);
		Haxis = glm::normalize(Haxis);

		m_forward = glm::rotate(m_forward, angle, yAxis);
		m_forward = glm::normalize(m_forward);

		m_up = glm::cross(m_forward, Haxis);
		m_up = glm::normalize(m_up);
	}

	inline glm::fvec3 GetLeft()
	{
		glm::fvec3 left = glm::cross(m_up, m_forward);
		left = glm::normalize(left);
		return left;
	}

	inline glm::fvec3 GetRight()
	{
		glm::fvec3 right = glm::cross(m_forward, m_up);
		right = glm::normalize(right);
		return right;
	}

	inline glm::fvec3 GetPos() const
	{
		return m_position;
	}

	inline glm::fvec3 GetUp() const
	{
		return m_up;
	}

	inline glm::fvec3 GetForward() const
	{
		return m_forward;
	}

	void AddToRenderingEngine(RenderingEngine* renderingEngine);

private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	glm::fvec3 yAxis = glm::fvec3(0, 1, 0);
};

