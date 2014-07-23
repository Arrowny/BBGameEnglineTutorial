#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "gameComponent.h"

#define COLOR_DEPTH 256

class CoreEngine;

struct Attenuation
{
	Attenuation() :
		m_constant(0.0),
		m_linear(0.0),
		m_exponent(1.0) {}

	Attenuation(const float& constant, const float& linear, const float& exponent) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}

	virtual ~Attenuation() {}

	float m_constant;
	float m_linear;
	float m_exponent;
};

struct BaseLight : public GameComponent
{
public:
	BaseLight() :
		m_color(glm::vec3(1, 1, 1)),
		m_intensity(0.0) {}

	BaseLight(const glm::vec3& color, const float& intensity) :
		m_color(color),
		m_intensity(intensity) {}

	virtual ~BaseLight() {}

	void addToEngine(CoreEngine* coreEngine);

	glm::vec3 m_color;
	GLfloat m_intensity;
	Shader* m_shader;
};

struct DirectionalLight : public BaseLight
{
public:
	DirectionalLight();
	DirectionalLight(const glm::vec3& color, const float& intensity);
	virtual ~DirectionalLight() {}
	glm::vec3 getDirection();
};

struct PointLight : public BaseLight
{
	PointLight();
	PointLight::PointLight(const glm::vec3& color, const float& intensity, const Attenuation& atten);
	virtual ~PointLight() {}
	glm::vec3 getPosition() { return getTransform()->m_trans; }

	Attenuation m_atten;
	glm::vec3 m_position;
	float m_range;
};

struct SpotLight : public PointLight
{
	SpotLight();
	SpotLight(const glm::vec3& color, const float& intensity, const Attenuation& atten, const float& cutoff = 0.5);
	virtual ~SpotLight() {}
	glm::vec3 getDirection();

	float m_cutoff;
};