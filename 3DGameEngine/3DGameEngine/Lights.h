#pragma once

#include <glm\glm.hpp>
#include "gameComponent.h"

class coreEngine;

struct baseLight : public gameComponent
{
public:
	glm::fvec3	m_color;
	float	m_intensity;

	baseLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0) :
		m_color(color),
		m_intensity(intensity) {}

	virtual void AddToEngine(coreEngine* engine);
	inline void SetShader(Shader* shader) { m_shader = shader; }
	inline Shader* GetShader() { return m_shader; }

protected:
private:
	Shader* m_shader;

};

struct directionalLight : public baseLight
{
	glm::fvec3 direction;

	directionalLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0);

};

struct Attenuation
{
	float m_constant;
	float m_linear;
	float m_exponent;

	Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}

};

struct pointLight : public baseLight
{
	Attenuation atten;
	glm::fvec3 position;
	float range;

	pointLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation());

};

struct spotLight : public pointLight
{
	glm::fvec3 direction;
	float cutoff;

	spotLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float cutoff = 0);

};
