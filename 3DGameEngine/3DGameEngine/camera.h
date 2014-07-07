#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "transform.h"
#include "Input.h"
#include "timing.h"

class Camera
{
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 lookAtPoint, glm::vec3 up, double zNear, double zFar, double fov, double screenWidth, double screenHeight);
	virtual ~Camera();

	void input(const Input& input);

	void reinitPerspectiveMatrix(double zNear, double zFar, double fov, double screenWidth, double screenHeight);
	void lookAt(const glm::vec3& lookAt, const glm::vec3& up);
	void move(const glm::vec3& dir, const float& amt);
	void rotateX(float angle);
	void rotateY(float angle);

	glm::vec3 getLeft();
	glm::vec3 getRight();
	glm::vec3 getCenter() { return m_center; }
	glm::vec3 getUp() { return m_up; }
	glm::mat4 getPerspectiveTransform() { return m_perspectiveTransform.getPerspectiveMatrix(); }
	glm::mat4 getCameraTransform() { return glm::lookAt(m_pos, m_pos + m_center, m_up); }
	glm::mat4 getProjectionTransform() { return m_perspectiveTransform.getPerspectiveMatrix() * glm::lookAt(m_pos, m_pos + m_center, m_up); }
	
	glm::vec3 m_pos;
private:
	Camera(const Camera& other) {}
	void operator=(const Camera& other) {}

	glm::vec3 findDirectionOfLookAt(glm::vec3 lookAt);
	glm::vec3 calculateTrueUp(glm::vec3 up, glm::vec3 center);

	Transform m_perspectiveTransform;
	
	glm::vec3 m_center;
	glm::vec3 m_up;
};

