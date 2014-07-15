#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "gameComponent.h"

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

struct BaseLight : public GameComponent
{
public:
	BaseLight() :
		m_color(glm::vec3(1, 1, 1)),
		m_intensity(0.0) {}

	BaseLight(glm::vec3 color, float intensity) :
		m_color(color),
		m_intensity(intensity) {}

	virtual ~BaseLight() {}

	void addToRenderingEngine(RenderingEngine* renderingEngine);

	glm::vec3 m_color;
	GLfloat m_intensity;
	Shader* m_shader;
};

struct DirectionalLight : public BaseLight
{
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 color, float intensity, glm::vec3 direction);
	virtual ~DirectionalLight() {}

	glm::vec3 m_direction;
};

struct PointLight : public BaseLight
{
	PointLight();
	PointLight(glm::vec3 color, float intensity, Attenuation atten, glm::vec3 position = glm::vec3(1, 1, 1), float range = 20);
	virtual ~PointLight() {}

	Attenuation m_atten;
	glm::vec3 m_position;
	float m_range;
};

struct SpotLight : public PointLight
{
	SpotLight();
	SpotLight(glm::vec3 color, float intensity, Attenuation atten, glm::vec3 position = glm::vec3(1, 1, 1), float range = 20, glm::vec3 direction = glm::vec3(0,0,1), float cutoff = 0.5);
	virtual ~SpotLight() {}

	glm::vec3 m_direction;
	float m_cutoff;
};