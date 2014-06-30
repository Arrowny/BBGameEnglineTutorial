#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up);
	~Camera();

	void move(glm::fvec3 dir, float amt);
	glm::fvec3 getLeft();
	glm::fvec3 getRight();
	void rotateX(float angle);
	void rotateY(float angle);

	const glm::fvec3 yAxis = glm::fvec3(0, 1, 0);

protected:
private:

	glm::fvec3 m_pos;
	glm::fvec3 m_forward;
	glm::fvec3 m_up;


};

