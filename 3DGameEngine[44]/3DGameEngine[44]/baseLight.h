#pragma once

#include <glm\glm.hpp>
#include "gameComponent.h"

struct baseLight : public gameComponent
{
public:
	glm::fvec3	m_color;
	float	m_intensity;

	baseLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0):
		m_color(color),
		m_intensity(intensity) {}

	virtual void AddToRenderingEngine(renderingEngine* renderingEngine);
	inline void SetShader(Shader* shader) { m_shader = shader; }
	inline Shader* GetShader() { return m_shader; }

protected:
private:
	Shader* m_shader;

};

