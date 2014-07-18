#pragma once
#include <glm\gtc\quaternion.hpp>

namespace quatMath{
	static glm::vec3 GetForward(glm::quat direct)
	{
		return glm::vec3(2.0f * (direct.x * direct.z - direct.w * direct.y), 2.0f * (direct.y * direct.z + direct.w * direct.x), 1.0f - 2.0f * (direct.x * direct.x + direct.y * direct.y));
	}

	static glm::vec3 GetBack(glm::quat direct)
	{
		return glm::vec3(-2.0f * (direct.x * direct.z - direct.w * direct.y), -2.0f * (direct.y * direct.z + direct.w * direct.x), -(1.0f - 2.0f * (direct.x * direct.x + direct.y * direct.y)));
	}

	static glm::vec3 GetUp(glm::quat direct)
	{
		return glm::vec3(2.0f * (direct.x*direct.y + direct.w*direct.z), 1.0f - 2.0f * (direct.x*direct.x + direct.z*direct.z), 2.0f * (direct.y*direct.z - direct.w*direct.x));
	}

	static glm::vec3 GetDown(glm::quat direct)
	{
		return glm::vec3(-2.0f * (direct.x*direct.y + direct.w*direct.z), -(1.0f - 2.0f * (direct.x*direct.x + direct.z*direct.z)), -2.0f * (direct.y*direct.z - direct.w*direct.x));
	}

	static glm::vec3 GetRight(glm::quat direct)
	{
		return glm::vec3(1.0f - 2.0f * (direct.y*direct.y + direct.z*direct.z), 2.0f * (direct.x*direct.y - direct.w*direct.z), 2.0f * (direct.x*direct.z + direct.w*direct.y));
	}

	static glm::vec3 GetLeft(glm::quat direct)
	{
		return glm::vec3(-(1.0f - 2.0f * (direct.y*direct.y + direct.z*direct.z)), -2.0f * (direct.x*direct.y - direct.w*direct.z), -2.0f * (direct.x*direct.z + direct.w*direct.y));
	}

}