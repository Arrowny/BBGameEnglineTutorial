#pragma once

#include <glm\glm.hpp>
#include "gameComponent.h"

class CoreEngine;

struct BaseLight : public GameComponent
{
public:
	glm::fvec3	m_color;
	float	m_intensity;

	BaseLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0) :
		m_color(color),
		m_intensity(intensity) {}

	virtual void AddToEngine(CoreEngine* engine);
	inline void SetShader(Shader* shader) { m_shader = shader; }
	inline Shader* GetShader() { return m_shader; }

protected:
private:
	Shader* m_shader;

};

struct DirectionalLight : public BaseLight
{
	glm::fvec3 direction;

	DirectionalLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0);

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

struct PointLight : public BaseLight
{
	Attenuation atten;
	glm::fvec3 position;
	float range;

	PointLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation());

};

struct SpotLight : public PointLight
{
	glm::fvec3 direction;
	float cutoff;

	SpotLight(const glm::fvec3& color = glm::fvec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float cutoff = 0);

};
