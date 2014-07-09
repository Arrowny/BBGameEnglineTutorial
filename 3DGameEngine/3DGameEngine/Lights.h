#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

struct Attenuation
{
	Attenuation() :
		m_constant(0.0),
		m_linear(0.0),
		m_exponent(1.0) {}

	Attenuation(float constant, float linear, float exponent) :
		m_constant(constant),
		m_linear(linear),
		m_exponent(exponent) {}

	virtual ~Attenuation() {}

	float m_constant;
	float m_linear;
	float m_exponent;
};

struct BaseLight
{
public:
	BaseLight() :
		m_color(glm::vec3(1, 1, 1)),
		m_intensity(0.0) {}

	BaseLight(glm::vec3 color, float intensity) :
		m_color(color),
		m_intensity(intensity) {}

	virtual ~BaseLight() {}

	glm::vec3 m_color;
	GLfloat m_intensity;
};

struct DirectionalLight
{
public:
	DirectionalLight() :
		m_base(BaseLight()),
		m_direction(glm::vec3(0, 0, 0)) {}

	DirectionalLight(BaseLight base, glm::vec3 direction) :
		m_base(base),
		m_direction(glm::normalize(direction)) {}

	virtual ~DirectionalLight() {}

	BaseLight m_base;
	glm::vec3 m_direction;
};

struct PointLight
{
	PointLight() :
		m_position(glm::vec3(0.0, 0.0, 0.0)) {}

	PointLight(BaseLight base, Attenuation atten, glm::vec3 position) :
		m_base(base),
		m_atten(atten),
		m_position(position) {}

	virtual ~PointLight() {}

	BaseLight m_base;
	Attenuation m_atten;
	glm::vec3 m_position;
};