#pragma once
#include <glm/glm.hpp>
#include "GameComponent.h"

struct BaseLight :public GameComponent
{
public:

	glm::vec3 color;
	float intensity;

	BaseLight() :
		color(glm::vec3(0, 0, 0)),
		intensity(1)
	{}
	BaseLight(glm::vec3 color, float intensity) :
		color(color),
		intensity(intensity)
	{}

	void AddToRenderingEngine(RenderingEngine* renderingEngine);
	inline void SetShader(Shader* shader) { l_shader = shader; }
	inline Shader* GetShader() { return l_shader; }

private:
	Shader* l_shader;
};

struct DirectionalLight :public BaseLight
{
public:
	//glm::vec3 color;
	//float intensity;
	glm::vec3 direction;

	DirectionalLight( glm::vec3 color = glm::vec3(0, 0, 0), float intensity = 0,  glm::vec3 direction = glm::vec3(0, 0, 0));
};

struct Attenuation
{
public:
	float constant;
	float linear;
	float exponent;
	Attenuation()
	{
		constant = 0.0;
		linear = 0.0;
		exponent = 1.0;
	}
	Attenuation(float constant, float linear, float exponent)
	{
		this->constant = constant;
		this->linear = linear;
		this->exponent = exponent;
	}

};


struct PointLight : public BaseLight
{
	Attenuation atten;
	glm::vec3 position;
	float range;

	PointLight(glm::vec3 color = glm::vec3(0, 0, 0), float intensity = 0, Attenuation attenu = Attenuation());

	
	void SetRange(float ran) { range = ran; }

};

struct SpotLight :public PointLight
{
public:
	glm::vec3 direction;
	float cutoff;

	SpotLight(glm::vec3 color , float intensity, Attenuation attenu ,glm::fvec3 direct, float cutoff);

	inline void SetDirection(glm::fvec3 direct) { direction = glm::normalize(direct); }
	inline void SetCutoff(float cutoff) { this->cutoff = cutoff; }
};




