#pragma once
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>

namespace EXQM
{
	//glm::mat4 toRotationMatrix(const glm::quat q)
	//{
	//	return glm::mat4(glm::vec4(GetForward(q), 0.0), glm::vec4(GetUp(q), 0.0), glm::vec4(GetRight(q), 0.0), glm::vec4(0.0,0.0,0.0,1.0));
	//}

	inline glm::vec3 GetForward(const glm::quat& q)
	{
		return glm::vec3(2.0f * (q.x * q.z - q.w * q.y), 2.0f * (q.y * q.z + q.w * q.x), 1.0f - 2.0f * (q.x * q.x + q.y * q.y));
	}

	inline glm::vec3 GetBack(const glm::quat& q)
	{
		return glm::vec3(-2.0f * (q.x * q.z - q.w * q.y), -2.0f * (q.y * q.z + q.w * q.x), -(1.0f - 2.0f * (q.x * q.x + q.y * q.y)));
	}

	inline glm::vec3 GetUp(const glm::quat& q)
	{
		return glm::vec3(2.0f * (q.x*q.y + q.w*q.z), 1.0f - 2.0f * (q.x*q.x + q.z*q.z), 2.0f * (q.y*q.z - q.w*q.x));
	}

	inline glm::vec3 GetDown(const glm::quat& q)
	{
		return glm::vec3(-2.0f * (q.x*q.y + q.w*q.z), -(1.0f - 2.0f * (q.x*q.x + q.z*q.z)), -2.0f * (q.y*q.z - q.w*q.x));
	}

	inline glm::vec3 GetRight(const glm::quat& q)
	{
		return glm::vec3(1.0f - 2.0f * (q.y*q.y + q.z*q.z), 2.0f * (q.x*q.y - q.w*q.z), 2.0f * (q.x*q.z + q.w*q.y));
	}

	inline glm::vec3 GetLeft(const glm::quat& q)
	{
		return glm::vec3(-(1.0f - 2.0f * (q.y*q.y + q.z*q.z)), -2.0f * (q.x*q.y - q.w*q.z), -2.0f * (q.x*q.z + q.w*q.y));
	}
};