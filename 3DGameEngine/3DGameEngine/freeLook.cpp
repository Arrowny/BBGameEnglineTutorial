#include "freeLook.h"


FreeLook::FreeLook()
{
}


FreeLook::~FreeLook()
{
}

void FreeLook::ProcessInput(Input* input, double delta)
{
	float movAmt = 500.0f;
	float rotAmt = -900000.0;

	glm::vec3 center = EXQM::GetForward(getTransform()->m_rot);
	glm::vec3 right = EXQM::GetRight(getTransform()->m_rot);
	glm::vec3 left = EXQM::GetLeft(getTransform()->m_rot);

	glm::vec3 yAxis(0.0, 1.0, 0);
	glm::vec3 xAxis = right;


	if (input->GetKeyDown(Input::KEY_W))
	{
		getTransform()->translate(center, movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_S))
	{
		getTransform()->translate(center, -movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_D))
	{
		getTransform()->translate(left, movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_A))
	{
		getTransform()->translate(right, movAmt*delta);
	}

	if (input->GetKeyDown(Input::KEY_UP))
	{
		getTransform()->rotate(-rotAmt*delta, xAxis);
	}

	if (input->GetKeyDown(Input::KEY_DOWN))
	{
		getTransform()->rotate(rotAmt*delta, xAxis);
	}

	if (input->GetKeyDown(Input::KEY_LEFT))
	{
		getTransform()->rotate(rotAmt*delta, yAxis);
	}

	if (input->GetKeyDown(Input::KEY_RIGHT))
	{
		getTransform()->rotate(-rotAmt*delta, yAxis);
	}

}
