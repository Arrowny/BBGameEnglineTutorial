#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Timing.h"
#include "Input.h"
#include "Window.h"
#include "gameComponent.h"

struct Camera : public gameComponent
{
public:
	Camera(float fov, float aspect, float zNear, float zFar)
	{
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(GetTransform().GetTransformedPos(), GetTransform().GetTransformedPos() + GetTransform().GetForward(), GetTransform().GetUp());
	} 

	bool mouseLocked = false;

	void input(const Input& input, float delta)
	{
		float sensitivity = 5.0f;
		float movAmt = (float)(10 * delta);
		//float rotAmt = (float)(200 * Time::getDelta());

		if (input.GetKey(input.KEY_ESCAPE))
		{
			input.SetCursor(true);

			mouseLocked = false;
		}

		if (mouseLocked)
		{
			glm::fvec2 centerPosition = glm::fvec2((float)Window::getWidth() / 2.0f, (float)Window::getHeight() / 2.0f);
			glm::fvec2 deltaPos = input.GetMousePosition() - centerPosition;

			bool rotY = deltaPos.x != 0;
			bool rotX = deltaPos.y != 0;

			if (rotY)
			{
				GetTransform().SetRot(GetTransform().GetRot() * glm::normalize(glm::angleAxis(glm::radians(deltaPos.x * sensitivity), yAxis)));
			}
				
			if (rotX)
			{
				GetTransform().SetRot(GetTransform().GetRot() * glm::normalize(glm::angleAxis(glm::radians(-deltaPos.y * sensitivity), GetTransform().GetRight())));
			}
				

			if (rotY || rotX){

				input.SetMousePosition(centerPosition);
			}
				
		}

		if (input.GetMouseDown(1))
		{
			glm::fvec2 centerPosition = glm::fvec2((float)Window::getWidth() / 2.0f, (float)Window::getHeight() / 2.0f);
			input.SetMousePosition(centerPosition);
			input.SetCursor(false);
			mouseLocked = true;
		}

		if (input.GetKey(input.KEY_W))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedForward(), movAmt * 3);
			}

			move(GetTransform().GetTransformedForward(), movAmt);
		}
		if (input.GetKey(input.KEY_S))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedForward(), -movAmt * 3);
			}

			move(GetTransform().GetTransformedForward(), -movAmt);
		}
		if (input.GetKey(input.KEY_A))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedLeft(), -movAmt * 3);
			}

			move(GetTransform().GetTransformedLeft(), -movAmt);
		}
		if (input.GetKey(input.KEY_D))
		{
			if (input.GetKey(input.KEY_LSHIFT))
			{
				move(GetTransform().GetTransformedRight(), -movAmt * 3);
			}

			move(GetTransform().GetTransformedRight(), -movAmt);
		}
		if (input.GetKey(input.KEY_SPACE))
			move(GetTransform().GetTransformedUp(), movAmt);
		if (input.GetKey(input.KEY_LCTRL))
			move(GetTransform().GetTransformedUp(), -movAmt);

		/*if (input.GetKey(input.KEY_UP))
			rotateX(-rotAmt);
		if (input.GetKey(input.KEY_DOWN))
			rotateX(rotAmt);
		if (input.GetKey(input.KEY_LEFT))
			rotateY(rotAmt);
		if (input.GetKey(input.KEY_RIGHT))
			rotateY(-rotAmt);*/

	}

	void move(glm::fvec3 dir, float amt)
	{
		GetTransform().SetPos(GetTransform().GetPos() + (dir * amt));
	}
	
	const glm::fvec3 yAxis = glm::fvec3(0, 1, 0);

	virtual void AddToRenderingEngine(renderingEngine* renderingEngine);

protected:
private:
	glm::mat4 projection;
};

