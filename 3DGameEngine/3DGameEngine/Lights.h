#pragma once
#include <glm/glm.hpp>
#include "Attenuation.h"

struct BaseLight
{
public:

	glm::vec3 color;
	float intensity;

	BaseLight() :
		color(glm::vec3(0, 0, 0)),
		intensity(1)
	{}
	BaseLight(glm::vec3& color, float intensity) :
		color(color),
		intensity(intensity)
	{}

};

struct DirectionalLight
{
public:
	BaseLight base;
	glm::vec3 direction;

	DirectionalLight() :
		base(BaseLight()),
		direction(glm::vec3(0, 0, 0))
	{}
	DirectionalLight(BaseLight base, glm::vec3 direction) :
		base(base),
		direction(glm::normalize(direction))
	{}

};

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	glm::vec3 position;
	float range;

	PointLight() :
		base(BaseLight()),
		atten(Attenuation()),
		position(glm::fvec3(0.0,0.0,0.0)),
		range(4.0)
	{}


	PointLight(BaseLight baselight, Attenuation attenu, glm::vec3 position, float range) :     //, float range
		base(baselight),
		atten(attenu),
		position(position),
		range(range)
	{}

	void SetPosition(glm::vec3 pos) { position = pos; }
	void SetRange(float ran) { range = ran; }
};

struct SpotLight
{
public:
	PointLight pointLight;
	glm::vec3 direction;
	float cutoff;

	SpotLight() :
		pointLight(PointLight()),
		direction(glm::fvec3(0.0, 0.0, 0.0)),
		cutoff(0)
	{}

	SpotLight(PointLight pointlight, glm::fvec3 direct, float cutoff) :
		pointLight(pointlight),
		direction(glm::normalize(direct)),
		cutoff(cutoff)
	{}
	inline PointLight* GetPointLight() { return &pointLight; }

	inline void SetDirection(glm::fvec3 direct) { direction = glm::normalize(direct); }
	inline void SetCutoff(float cutoff) { this->cutoff = cutoff; }
};



