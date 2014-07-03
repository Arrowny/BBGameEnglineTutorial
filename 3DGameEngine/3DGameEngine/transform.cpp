#include "transform.h"


Transform::~Transform()
{
}

glm::mat4 Transform::getTransformation() const
{
	glm::mat4 transMat = glm::translate(m_trans);
	glm::mat4 scaleMat = glm::scale(m_scale);

	glm::mat4 rotXMat = glm::rotate(m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotYMat = glm::rotate(m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotZMat = glm::rotate(m_rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotMat = rotZMat * rotYMat * rotXMat; //TODO: use quaternions to generate rotation matrix

	return transMat * rotMat * scaleMat;
}


