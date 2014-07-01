#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Timing.h"
#include "Input.h"

struct Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);

	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	void input(const Input& input)
	{
		
		float movAmt = (float)(5 * Time::getDelta());
		float rotAmt = (float)(200 * Time::getDelta());

		if (input.GetKey(input.KEY_W))
			move(forward, movAmt);
		if (input.GetKey(input.KEY_S))
			move(forward, -movAmt);
		if (input.GetKey(input.KEY_A))
			move(getLeft(), movAmt);
		if (input.GetKey(input.KEY_D))
			move(getRight(), movAmt);

		if (input.GetKey(input.KEY_UP))
			rotateX(-rotAmt);
		if (input.GetKey(input.KEY_DOWN))
			rotateX(rotAmt);
		if (input.GetKey(input.KEY_LEFT))
			rotateY(rotAmt);
		if (input.GetKey(input.KEY_RIGHT))
			rotateY(-rotAmt);

	}

	void move(glm::fvec3 dir, float amt){

		pos = pos + (dir*amt);

	}
	
	glm::fvec3 getLeft(){

		glm::fvec3 left = glm::cross(up, forward);
		glm::normalize(left);
		return left;

	}

	glm::fvec3 getRight(){

		glm::fvec3 right = glm::cross(forward, up);
		glm::normalize(right);
		return right;

	}

	void Camera::rotateX(float angle){

		glm::fvec3 hAxis = glm::cross(yAxis, forward);
		glm::normalize(hAxis);

		forward = glm::vec3((glm::rotate(angle, hAxis) * glm::fvec4(forward, 0.0)));
		glm::normalize(forward);

		up = glm::cross(forward, hAxis);
		glm::normalize(up);

	}

	void Camera::rotateY(float angle){

		glm::fvec3 hAxis = glm::cross(yAxis, forward);
		glm::normalize(hAxis);

		forward = glm::vec3((glm::rotate(angle, yAxis) * glm::fvec4(forward, 0.0)));
		glm::normalize(forward);

		up = glm::cross(forward, hAxis);
		glm::normalize(up);

	}

	const glm::fvec3 yAxis = glm::fvec3(0, 1, 0);

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

//class Camera
//{
//public:
//	Camera();
//	Camera(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up);
//	~Camera();
//
//	void move(glm::fvec3 dir, float amt);
//	inline glm::fvec3 getForward() { return m_forward; };
//	inline glm::fvec3 getUp() { return m_up; };
//	glm::fvec3 getLeft();
//	glm::fvec3 getRight();
//	void rotateX(float angle);
//	void rotateY(float angle);
//
//	const glm::fvec3 yAxis = glm::fvec3(0, 1, 0);
//
//protected:
//private:
//
//	glm::fvec3 m_pos;
//	glm::fvec3 m_forward;
//	glm::fvec3 m_up;
//
//
//};

