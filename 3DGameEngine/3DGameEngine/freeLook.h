#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Timing.h"
#include "Input.h"
#include "Window.h"
#include "gameComponent.h"

struct FreeLook : public gameComponent
{
public:
	virtual void AddToEngine(coreEngine* engine);

	bool mouseLocked = false;

	virtual void input(const Input& input, float delta)
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

	}

	const glm::fvec3 yAxis = glm::fvec3(0, 1, 0);

protected:
private:
	float m_sensitivity;
	int m_unlockMouseKey;
};

