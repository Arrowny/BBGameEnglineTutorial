#pragma once
//#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include "Input.h"
#include "timing.h"
#include "Window.h"
#include "GameComponent.h"
#include "math.h"


class Camera :public GameComponent
{
public:
	Camera(/*const glm::vec3& pos,*/ float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);

	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(GetTransform().GetPos(), GetTransform().GetPos() + GetTransform().GetForward(), GetTransform().GetUp());
		
	}

	inline glm::mat4 GetOrthographic(float left, float right, float bottom, float top, float near, float far) const
	{
		return glm::ortho(left, right, bottom, top, near, far);
	}

	bool mouselocked = false;

	glm::vec2 centerPosition = glm::vec2(WindowParameter::width / 2, WindowParameter::height / 2);

	void input(Input input, float delta)
	{
		float sensitivity = -3.0f;

		float movAmt = (float)(10 * delta);
		float rotAmt = (float)(300 * delta);

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
				GetTransform().SetRot(GetTransform().GetRot()* glm::normalize(glm::angleAxis(glm::radians(-deltaPos.x * sensitivity), yAxis)));
				//RotateY(-deltaPos.x * sensitivity);
			if (rotX)
				GetTransform().SetRot(GetTransform().GetRot() * glm::normalize(glm::angleAxis(glm::radians(deltaPos.y * sensitivity), GetTransform().GetRight())));
				//RotateX(deltaPos.y * sensitivity);
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
			move(GetTransform().GetForward(), movAmt);
		if (input.GetKey(input.KEY_S))
			move(GetTransform().GetForward(), -movAmt);
		if (input.GetKey(input.KEY_A))
			move(GetTransform().GetLeft(), -movAmt);
		if (input.GetKey(input.KEY_D))
			move(GetTransform().GetRight(), -movAmt);

		if (input.GetKey(input.KEY_CAPSLOCK))
			move(GetTransform().GetUp(), movAmt);
		if (input.GetKey(input.KEY_LSHIFT))
			move(GetTransform().GetUp(), -movAmt);

		//if (input.GetKey(input.KEY_UP))
		//	GetTransform().SetRot(GetTransform().GetRot() * glm::normalize(glm::angleAxis(glm::radians(rotAmt), GetTransform().GetRight())));
		//	//RotateX(-rotAmt);
		//if (input.GetKey(input.KEY_DOWN))
		//	GetTransform().SetRot(GetTransform().GetRot() * glm::normalize(glm::angleAxis(glm::radians(-rotAmt), GetTransform().GetRight())));
		//if (input.GetKey(input.KEY_LEFT))
		//	GetTransform().SetRot(GetTransform().GetRot() * glm::normalize(glm::angleAxis(glm::radians(-rotAmt), yAxis)));
		//	//RotateY(rotAmt);
		//if (input.GetKey(input.KEY_RIGHT))
		//	GetTransform().SetRot(GetTransform().GetRot() * glm::normalize(glm::angleAxis(glm::radians(rotAmt), yAxis)));
			//RotateY(-rotAmt);
	}

	inline void move(glm::fvec3 dir, float amt)
	{
		//GetTransform().GetPos() += (dir * amt);
		GetTransform().SetPos(GetTransform().GetPos() + (dir * amt));
	}


	void AddToEngine(coreEngine* engine);

private:
	glm::mat4 m_perspective;

	glm::fvec3 yAxis = glm::fvec3(0, 1, 0);
};

