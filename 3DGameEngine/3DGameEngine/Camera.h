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
		/*glm::mat4 cameraRotation = glm::mat4_cast(glm::conjugate(GetTransform().GetTransformedRot()));
		glm::mat4 cameraTranslation;

		cameraTranslation = glm::translate(GetTransform().GetTransformedPos());

		return projection * cameraRotation * cameraTranslation;*/
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
			move(GetTransform().GetForward(), movAmt);
		if (input.GetKey(input.KEY_S))
			move(GetTransform().GetForward(), -movAmt);
		if (input.GetKey(input.KEY_A))
			move(GetTransform().GetLeft(), -movAmt);
		if (input.GetKey(input.KEY_D))
			move(GetTransform().GetRight(), -movAmt);
		if (input.GetKey(input.KEY_SPACE))
			move(GetTransform().GetUp(), movAmt);
		if (input.GetKey(input.KEY_LCTRL))
			move(GetTransform().GetUp(), -movAmt);

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

